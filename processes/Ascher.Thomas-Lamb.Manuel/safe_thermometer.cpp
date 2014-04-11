#include "safe_thermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

SafeThermometer::SafeThermometer(Thermometer* unsafe_thermometer)
	:_unsafe_thermometer(unsafe_thermometer)
{

}

SafeThermometer::~SafeThermometer()
{
	delete _unsafe_thermometer;
}

double SafeThermometer::get_temperature() const
{
	double temperature = 0.0;
	int pipe_fd[2];
	char temperature_chars[64];

	int err = pipe(pipe_fd);
	if (err == -1)
	{
		throw ThermometerException("could not open pipe for child process");
	}

	pid_t pid = fork();
	if (pid == -1)
	{
		throw ThermometerException("could not fork child process");
	}
	else if (pid == 0)
	{
		close(pipe_fd[0]);

		temperature = _unsafe_thermometer->get_temperature();
		sprintf(temperature_chars, "%f", temperature);
	
		ssize_t written = write(pipe_fd[1], temperature_chars, strlen(temperature_chars) * sizeof(char));
		if (written == -1)
		{
			abort();
		}

		close(pipe_fd[1]);  
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);

		ssize_t nread = read(pipe_fd[0], temperature_chars, sizeof(temperature_chars));
		close(pipe_fd[0]);
		
		if (nread < 0)
		{
			throw ThermometerException("could not read temperature from pipe");
		}
    }	
	
	return _unsafe_thermometer->get_temperature();
}
