#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"

class SafeThermometer : public Thermometer
{
public:
	SafeThermometer(Thermometer* unsafe_thermometer);

    virtual double get_temperature() const;
    
private:
	Thermometer* _unsafe_thermometer;
};

#endif
