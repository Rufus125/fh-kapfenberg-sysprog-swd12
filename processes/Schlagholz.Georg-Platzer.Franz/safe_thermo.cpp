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
	int child = fork();
	if (child == -1) {
		perror("fork");
		return 1;
	} else if (child == 0) {
		//child
		//alarm
		exit(0);
	} else {
		//pause
		waitpid(child);
	}
	return 0;
}
