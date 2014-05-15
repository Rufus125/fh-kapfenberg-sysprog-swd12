#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "safe_thermometer.h"

SafeThermometer::SafeThermometer(Thermometer* unstable_thermometer, unsigned int timeout) :
	_unstable_thermometer(unstable_thermometer), _timeout(timeout){
}

//Temp. mit fork in eigenem Prozess
double SafeThermometer::get_temperature() const
{
	int p_fd[2];
	int p_error = pipe(p_fd);
	double temp = 0.0;
	char temp_s[64];

	pid_t pid = fork();

	//check for some errors
	if(p_error == -1)
	{
		throw ThermometerException("pipe error");
	}
	else if(pid == -1)
	{
		throw ThermometerException("fork error");
	}
	else if(pid == 0)
	{
		close(p_fd[0]);
		alarm(_timeout);
		temp = _unstable_thermometer -> get_temperature();
		sprintf(temp_s, "%f", temp);
		ssize_t p_write = write(p_fd[1], temp_s, sizeof(temp_s));
		if(p_write == -1)
		{
			throw ThermometerException("temp write error");
			close(p_fd[1]);
			exit(EXIT_FAILURE);
		}
		
		close(p_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		int status = 0;
		close(p_fd[1]);
		waitpid(pid, &status, 0);
		if(!WIFEXITED(status))
		{
			throw ThermometerException("child process exit failure");
			close(p_fd[0]);
		}
		else
		{
			ssize_t p_read = read(p_fd[0], temp_s, sizeof(temp_s));

			if(p_read <= 0)
			{
				throw ThermometerException("error reading tempe");
				close(p_fd[0]);
			}
			else
			{
				temp = atof(temp_s);
			}
			close(p_fd[0]);
		}
	}

	return temp;
}
