#include "safe_thermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


SafeThermometer::SafeThermometer(Thermometer* thermometer):thermometer(thermometer){}

SafeThermometer::~SafeThermometer() {
	delete thermometer;
}

double SafeThermometer::get_temperature() const
{
	
	
	
	return 0;
}
