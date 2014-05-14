#include "thermometer.h"
#include "save_thermometer.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define TIMEOUT 10

SafeThermometer::SafeThermometer(Thermometer *thermometer) : Thermometer() {
	this->thermometer = thermometer;
}

SafeThermometer::~SafeThermometer()
{
	delete thermometer;
}

double SafeThermometer::get_temperature() const {
	int pipe_fd[2];

	if(pipe(pipe_fd) == -1) {
		throw ThermometerException("error opening pipe");
	}

	pid_t pid = fork();
	if(pid == -1) {
		throw ThermometerException("fork failed");


	} else if (pid == 0) {
		close(pipe_fd[0]);

		alarm(TIMEOUT);

		char send_str[64];

		double temp = this->thermometer->get_temperature();
		sprintf(send_str, "%f", temp);

		ssize_t numSent = write(pipe_fd[1], send_str, (strlen(send_str)+1) + sizeof (char));
		close(pipe_fd[1]);

		if (numSent <= 0) {
			abort();
		}

		exit(EXIT_SUCCESS);

	} else {
		close(pipe_fd[1]);

		int state = 0;
		waitpid(pid, &state, 0);
		if(!WIFEXITED(state)) {
			close(pipe_fd[0]);
			throw ThermometerException("thermometer timed out");
		}

		char read_str[64];

		ssize_t numRead = read(pipe_fd[0], read_str, sizeof(read_str));
		close(pipe_fd[1]);

		if (numRead <= 0) {
			throw ThermometerException("could not retrieve temperature");
		}

		return atof(read_str);
	}

}
