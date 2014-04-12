#include "safe_thermo.h"
using namespace std;


SafeThermometer::SafeThermometer(Thermometer* unstableThermometer, unsigned long timeout)
	:unstableThermometer(unstableThermometer), timeout(timeout){

}
SafeThermometer::~SafeThermometer(){
delete unstableThermometer;
}

double SafeThermometer::get_temperature() const{
	int child = fork();

	if(child ==-1){
		perror("fork");
		return 1;
	}
	else if (child==0) {
		//alarm
	}
	else {
		//waitpid()
	}
	return 0;
}
