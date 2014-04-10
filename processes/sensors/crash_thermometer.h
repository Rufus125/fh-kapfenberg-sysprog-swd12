#ifndef CRASH_THERMOMETER_H
#define CRASH_THERMOMETER_H

#include "thermometer.h"

class CrashThermometer : public Thermometer
{
public:
    virtual double get_temperature() const;
};

#endif
