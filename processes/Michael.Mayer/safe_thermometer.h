#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"

class SafeThermometer : public Thermometer
{
public:
    SafeThermometer(unsigned int timeout, Thermometer* thermometer);
    virtual double get_temperature() const;

private:
    unsigned int _timeout;
    Thermometer* _thermometer;

};

#endif

