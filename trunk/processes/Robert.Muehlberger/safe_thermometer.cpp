#include "safe_thermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
// Implementation of the constructor
SafeThermometer::SafeThermometer(Thermometer* sandTherm, int tout){
	sandboxThermometer = sandTherm;
	timeout = tout;
}
// Implementation of the deconstructor
SafeThermometer::~SafeThermometer() {
	delete sandboxThermometer;
}
// Implementation ot the delegate get_temperatur method
double SafeThermometer::get_temperature() const{
	
	int pipe_fd[2]; // pipe_fd[0] to read; pipe_fd[1] to write

	int err = pipe(pipe_fd); // Init pipe
	
	if (err == -1){ // Some error occurs at init pipe
		throw ThermometerException("could not open pipe for temperature query");
	} // if

	double temperature = 0.0;
	char temperature_chars[64];
	pid_t pid;
	switch (pid = fork()) { // Init fork
		
		case -1: // Some error occours at init fork
			throw ThermometerException("Function fork did not work");
			break;
			
		case 0: // Child process
			close(pipe_fd[0]); // close read from pipe

			alarm(timeout); // Start timer
			temperature = sandboxThermometer->get_temperature();
			sprintf(temperature_chars, "%f", temperature);
			
			// Write into pipe the temperature
			if(!(write(pipe_fd[1], temperature_chars, (strlen(temperature_chars) + 1) * sizeof(char))))
				abort();
			

			close(pipe_fd[1]);  
			exit(EXIT_SUCCESS);
			break;
			
		default: // Parent process
			close(pipe_fd[1]); // close write from pipe
			
			int status = 0;
			waitpid(pid, &status, 0); // Wait vor terminating child process
			
			// Terminate child process normaly = 1
			if (!WIFEXITED(status)) { // Some 
				close(pipe_fd[0]);			
				throw ThermometerException("Could not read from pipe or time is over");
			}
			
			// Read from pipe
			ssize_t nread = read(pipe_fd[0], temperature_chars, sizeof(temperature_chars));
			close(pipe_fd[0]);
			
			if (nread <= 0) { // No values could read
				throw ThermometerException("could not read from pipe");
			} else {
				temperature = atof(temperature_chars);
			}
			break;
		} // case	
	
	return temperature;
}
