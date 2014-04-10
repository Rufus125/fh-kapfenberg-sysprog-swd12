#ifndef FIXED_THERMOMETER_H
#define FIXED_THERMOMETER_H

#include "thermometer.h"

class FixedThermometer : public Thermometer
{
public:
    FixedThermometer(double temperature) : _temperature(temperature) {}
    virtual double get_temperature() const
    {
        return _temperature;
    }

private:
    double _temperature;
};

#endif
