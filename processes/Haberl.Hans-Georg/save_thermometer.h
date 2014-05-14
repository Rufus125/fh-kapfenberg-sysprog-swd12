#ifndef __SAFE_THERMOMETER__
#define __SAFE_THERMOMETER__

#include "thermometer.h"

class SafeThermometer: public Thermometer {
private:
	Thermometer *thermometer;

public:
	SafeThermometer(Thermometer *thermometer);
	virtual ~SafeThermometer();
	virtual double get_temperature() const;
};

#endif
