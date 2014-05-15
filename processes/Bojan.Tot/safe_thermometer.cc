#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "safe_thermometer.h"

SafeThermometer::SafeThermometer(Thermometer* unstable_thermometer,
		unsigned int timeout) :
		_unstable_thermometer(unstable_thermometer), _timeout(timeout) {

}

double SafeThermometer::get_temperature() const {

	int fd[2];
	pid_t pid;
	ssize_t temperature;
	char tmpBuf[20];
	double tmp = 0.0;

	pipe(fd);

	if ((pid = fork()) == -1) {
		perror("fork");
		exit (EXIT_FAILURE);
	}

	if (pid == 0) {
		close(fd[0]);
		alarm(2);
		tmp = _unstable_thermometer->get_temperature();
		sprintf(tmpBuf, "%f", tmp);
		write(fd[1], tmpBuf, sizeof(tmpBuf));
		close(fd[1]);
		exit (EXIT_SUCCESS);
	} else {
		close(fd[1]);
		waitpid(pid, NULL, 0);
		temperature = read(fd[0], tmpBuf, sizeof(tmpBuf));

		if (temperature <= 0) {
			throw ThermometerException("Can't read Temperature");
			close(fd[0]);
			exit (EXIT_FAILURE);
		}

		tmp = atof(tmpBuf);

		close(fd[0]);

	}

	return temperature;
}
