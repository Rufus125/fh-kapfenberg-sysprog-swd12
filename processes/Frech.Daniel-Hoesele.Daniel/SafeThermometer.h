// Daniel Hoesele - Daniel Frech - SWD12

#include "../sensors/thermometer.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

class SafeThermometer : public Thermometer {
	public:
		SafeThermometer(Thermometer* unstableThermometer, unsigned int timeout = 10);
		virtual ~SafeThermometer();
		virtual double get_temperature() const;

	private:
		Thermometer* unstableThermometer;
		unsigned int timeout;
		static const int BUFFER_SIZE = 64;
};
