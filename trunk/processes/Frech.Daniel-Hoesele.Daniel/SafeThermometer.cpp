// Daniel Hoesele - Daniel Frech - SWD12

#include "SafeThermometer.h"

using namespace std;

SafeThermometer::SafeThermometer(Thermometer* unstableThermometer,
		unsigned int timeout):
		unstableThermometer(unstableThermometer), timeout(timeout){}

SafeThermometer::~SafeThermometer() {
	delete unstableThermometer;
}

double SafeThermometer::get_temperature() const {

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

	} else if (pid == 0) {
		// child. close parent's end.
		close(pipe_fd[0]);
		alarm(timeout);

		double temperature = unstableThermometer->get_temperature();
		char buffer[BUFFER_SIZE];
		snprintf(buffer, BUFFER_SIZE, "%f", temperature);
		ssize_t written= write(pipe_fd[1], buffer, BUFFER_SIZE);

		if(written < 0){
			perror("write");
		}
		// parent. close child's end.
		close(pipe_fd[1]);
		exit(0);

	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);

		if(status == 0) {
			char buffer[BUFFER_SIZE];
            ssize_t nread = read(pipe_fd[0], buffer, BUFFER_SIZE);

            if (nread > 0) {
                return atof(buffer);
            }
            else {
                throw ThermometerException("failed to get temperature");
            }		
		} else {
			throw ThermometerException("unstable thermometer exception thrown");
		}
	}
}
