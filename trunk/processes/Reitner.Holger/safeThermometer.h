#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "../sensors/thermometer.h"

class SafeThermometer : public Thermometer
{
public:
	SafeThermometer(Thermometer* unstableThermometer, unsigned int timeout = 2);

	virtual ~SafeThermometer();

    virtual double get_temperature() const;
    
private:
	Thermometer* _unstableThermometer;
	
	unsigned int _timeout;
};

#endif
