#include "safe_thermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

SafeThermometer::SafeThermometer(Thermometer* unstable_thermometer, unsigned int timeout)
	:_unstable_thermometer(unstable_thermometer)
	,_timeout(timeout)
{

}

SafeThermometer::~SafeThermometer()
{
	delete _unstable_thermometer;
}

double SafeThermometer::get_temperature() const
{
	int pipe_fd[2];

	int err = pipe(pipe_fd);
	if (err == -1)
	{
		throw ThermometerException("could not open pipe for temperature query");
	}

	double temperature = 0.0;
	char temperature_chars[64];

	pid_t pid = fork();
	if (pid == -1)
	{
		throw ThermometerException("could not fork process for temperature query");
	}
	else if (pid == 0)
	{
		close(pipe_fd[0]);

		alarm(_timeout);
		temperature = _unstable_thermometer->get_temperature();
		sprintf(temperature_chars, "%f", temperature);
	
		ssize_t written = write(pipe_fd[1], temperature_chars, (strlen(temperature_chars) + 1) * sizeof(char));
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
		
		int status = 0;
		waitpid(pid, &status, 0);
		
		if (!WIFEXITED(status))
		{
			close(pipe_fd[0]);			
			throw ThermometerException("could not query temperature due to crash or timeout");
		}

		ssize_t nread = read(pipe_fd[0], temperature_chars, sizeof(temperature_chars));
		close(pipe_fd[0]);
		
		if (nread <= 0)
		{
			throw ThermometerException("could not query temperature");
		}
		else
		{
			temperature = atof(temperature_chars);
		}
    }	
	
	return temperature;
}
