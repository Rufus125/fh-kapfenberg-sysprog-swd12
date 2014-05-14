#include "thermometer.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

class SafeThermometer : public Thermometer
{
private:
	Thermometer * unstableThermometer;
	unsigned long timeout;
	static const int DOUBLE_SIZE = 64;
public:
	~SafeThermometer();
	SafeThermometer(Thermometer* unstableThermometer, unsigned long timeout = 6);
	virtual double get_temperature() const;
};
