#include "safe_thermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

#define DOUBLE_SIZE sizeof(double)*8


SafeThermometer::SafeThermometer(Thermometer* thermometer):thermometer(thermometer){}

SafeThermometer::~SafeThermometer() {
	delete thermometer;
}

double SafeThermometer::get_temperature() const
{
 int pipe_fd[2];

    int err = pipe(pipe_fd);
    if (err == -1) {
        perror("pipe");
        abort();
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        abort();
    }
    else if (pid == 0) {
		//set alarm
		alarm(2);
		
        // child. close parent's end.
        close(pipe_fd[0]);
        
        //load temperature from real sensor
        double tempValue = thermometer->get_temperature();
        char tempChar[DOUBLE_SIZE];
        sprintf(tempChar,"%f",tempValue);
        
        //read data to parent process
        ssize_t pipeWrite = write(pipe_fd[1], tempChar, DOUBLE_SIZE); 
        if (pipeWrite < 0)
        {
			perror("pipe write error");
		}

        // done; close pipe so parent can realize we are done
        close(pipe_fd[1]);
        // important: do not escape into parent code        
        exit(0);
    }
    else {
		// parent. close child's end.
        close(pipe_fd[1]);
		int childState;
		
		//wait for child process
		waitpid(pid, &childState, 0);
		

        if (childState == 0)
        {
			char doubleBuffer[DOUBLE_SIZE];
			ssize_t pipeRead = read(pipe_fd[0], doubleBuffer, DOUBLE_SIZE);
			if(pipeRead > 0)
			{
				return atof(doubleBuffer);	
			} else
			{
				perror("read from sensor");
				throw ThermometerException("ThermometerException");
			}
			
		} else
		{
			throw ThermometerException("ThermometerException");
		}

    }
    
    return 0;
}
