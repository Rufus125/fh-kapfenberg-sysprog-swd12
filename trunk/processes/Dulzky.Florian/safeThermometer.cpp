#include "safeThermometer.h"
using namespace std;

SafeThermometer::SafeThermometer(Thermometer* thermo, unsigned long timeout) :
		thermo(thermo), timeout(timeout) {

}

double SafeThermometer::get_temperature() const {
	int pipe_fd[2];
	int err = pipe(pipe_fd);
	if (err == -1) {
		cerr << "pipe()" << endl;
		return 1;
	}

	pid_t child = fork();
	if (child == -1) {
		cerr << "fork()" << endl;
		return 1;
	} else if (child == 0) {
		close(pipe_fd[0]);

		alarm(timeout);

		double temperature = thermo->get_temperature();
		char tmp[DOUBLE_SIZE];
		snprintf(tmp,DOUBLE_SIZE, "%f", temperature);

		ssize_t written = write(pipe_fd[1], tmp, DOUBLE_SIZE); 
		if(written < 0){
			perror("Temperatur lesen");
		}

		close(pipe_fd[1]);

		exit(0);
	} else {
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
				cerr << "Temp. kann nicht gelesen werden" << endl;
            }		
		}else{
			cerr << "Instabil!!" << endl;
		}
	}
}
