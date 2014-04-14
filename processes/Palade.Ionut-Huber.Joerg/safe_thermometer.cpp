#include "safe_thermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

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
        char tempChar[sizeof(double)*8];
        sprintf(tempChar,"%f",tempValue);
        
        //read data to parent process
        ssize_t pipeWrite = write(pipe_fd[1], tempChar, sizeof(double)*8); 
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
			char doubleBuffer[sizeof(double)*8];
			ssize_t pipeRead = read(pipe_fd[0], doubleBuffer, sizeof(double)*8);
			if(pipeRead > 0)
			{
				return atof(doubleBuffer);	
			} else
			{
				perror("read from sensor error");
				throw ThermometerException("ThermometerException");
			}
			
		} else
		{
			throw ThermometerException("ThermometerException");
		}
           

        
        
        for (;;) {
            char readbuf[3];
            ssize_t nread = read(pipe_fd[0], readbuf, sizeof(readbuf)*8);
            if (nread > 0) {
                cout << nread << ':';
                cout.write(readbuf, nread);
                cout << endl;
            }
            else if (nread == 0) {
                cerr << "\n<<< END OF INPUT" << endl;
                break;
            }
            else {
                perror("read");
                abort();
            }
        }
    }
            return 0;
}
