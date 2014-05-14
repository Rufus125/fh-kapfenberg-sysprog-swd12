#include "safe_thermo.h"
using namespace std;

SafeThermometer::SafeThermometer(Thermometer* unstableThermometer,
		unsigned long timeout) :
		unstableThermometer(unstableThermometer), timeout(timeout) {

}
SafeThermometer::~SafeThermometer() {
	delete unstableThermometer;
}


double SafeThermometer::get_temperature() const {
	int pipe_fd[2];
	int err = pipe(pipe_fd);
	if (err == -1) {
		perror("pipe");
		return 1;
	}

	pid_t child = fork();
	if (child == -1) {
		perror("fork");
		return 1;
	} else if (child == 0) {
		//child, close parent pipe (reading)
		close(pipe_fd[0]);

		alarm(timeout);

		double temperature = unstableThermometer->get_temperature();
		char tmp[DOUBLE_SIZE];
		snprintf(tmp,DOUBLE_SIZE, "%f", temperature);

		ssize_t written = write(pipe_fd[1], tmp, DOUBLE_SIZE); 
		if(written < 0){
			perror("write temperature");
		}

		close(pipe_fd[1]);

		exit(0);
	} else {
		// parent, close child pipe (writing)
		close(pipe_fd[1]);
		int status;
		waitpid(child, &status, 0);

		if(status == 0){
			char readbuf[DOUBLE_SIZE];
            ssize_t nread = read(pipe_fd[0], readbuf, DOUBLE_SIZE);
            if (nread > 0) {
                return atof(readbuf);
            }
            else {
                throw ThermometerException("Could not read temperature from unstable thermometer!");
            }		
		}else{
			throw ThermometerException("Unstable thermometer!");
		}
	}
}
