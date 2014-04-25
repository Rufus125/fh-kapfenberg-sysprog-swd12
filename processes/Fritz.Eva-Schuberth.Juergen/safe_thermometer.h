#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"

class SafeThermometer : public Thermometer
{
public:
	SafeThermometer(Thermometer* unstable_thermometer);

	virtual ~SafeThermometer();

    virtual double get_temperature() const;
    
private:
	Thermometer* _unstable_thermometer;
};

#endif
