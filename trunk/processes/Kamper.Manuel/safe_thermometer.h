#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"

//Extend thermometer.h
class SafeThermometer : public Thermometer
{
	public:
		SafeThermometer(Thermometer* unstable_thermometer, unsigned int timeout = 2);
		virtual double get_temperature() const;

	private:
		Thermometer* _unstable_thermometer;
		unsigned int _timeout;
};

#endif
