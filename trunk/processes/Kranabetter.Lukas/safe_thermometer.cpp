#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "safe_thermometer.h"

/**
 * Safe thermometer implementation<br>
 *
 * @see safe_thermometer.h
 *
 * @author Lukas Kranabetter
 */
SafeThermometer::SafeThermometer(Thermometer* unstable_thermometer, unsigned int timeout) :
																	_unstable_thermometer(unstable_thermometer),
																	_timeout(timeout)
{

}

/**
 * Get the temperature in a separated process<br>
 *
 * Note about why we should close pipes:<br>
 * If your pipe spans processes (i.e. is created before a fork() and then the parent and child use it to communicate)<br>
 * you can have one write and and one read end. Then it is good practice to close the unwanted ends of the pipe.<br>
 * This will make sure that when the writing end closes the pipe it is seen by the read end.<br>
 * As an example, say the child is the write side, and it dies. If the parent write side has not been closed,<br>
 * then the parent will not get "eof" (zero length read()) from the pipe - because the pipe has a open write-end.<br>
 * make it clear which process is doing the writing and which process is doing the reading on the pipe.<br>
 */
double SafeThermometer::get_temperature() const
{
	int pipe_fd[2];
	int pipe_error = pipe(pipe_fd);
	double temperature = 0.0;
	char temperature_string[64];

	// Fork a new process and get its id
	pid_t pid = fork();

	// Check initialization errors
	if(pipe_error == -1)
	{
		throw ThermometerException("SafeThermometer pipe error");
		abort();
	}
	else if(pid == -1)
	{
		throw ThermometerException("SafeThermometer fork process error");
		abort();
	}
	else if(pid == 0)
	{
		// Handle child process

		// Close parent pipe
		close(pipe_fd[0]);
		// Implement timeout with alarm
		alarm(_timeout);
		// Get the temperature from a certain unstable thermometer
		temperature = _unstable_thermometer -> get_temperature();
		// Write the temperature value formatted to a string
		sprintf(temperature_string, "%f", temperature);
		// Write the temperature as string to the pipe output
		ssize_t pipe_write = write(pipe_fd[1], temperature_string, sizeof(temperature_string));
		// Abort on error
		if(pipe_write == -1)
		{
			throw ThermometerException("SafeThermometer child can't write temperature");
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
		// Close child pipe
		close(pipe_fd[1]);
		// Do not escape into parent code, use exit and not abort so parent can realize we are done
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Handle parent process
		int status = 0;

		// Close child pipe
		close(pipe_fd[1]);
		// Wait for child process
		waitpid(pid, &status, 0);
		// Catch not normal child process exit status
		if(!WIFEXITED(status))
		{
			throw ThermometerException("SafeThermometer child process exit failure");
			close(pipe_fd[0]);
			abort();
		}
		else
		{
			// Read from unstable thermometer pipe to return the value in safe thermometer
			ssize_t pipe_read = read(pipe_fd[0], temperature_string, sizeof(temperature_string));

			if(pipe_read <= 0)
			{
				throw ThermometerException("SafeThermometer parent can't read temperature");
				close(pipe_fd[0]);
				abort();
			}
			else
			{
				// Convert string from pipe to double temperature value
				temperature = atof(temperature_string);
			}
			// Close pipe after reading
			close(pipe_fd[0]);
		}
	}

	return temperature;
}
