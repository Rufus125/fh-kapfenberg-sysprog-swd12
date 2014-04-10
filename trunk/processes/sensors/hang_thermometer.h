#ifndef HANG_THERMOMETER_H
#define HANG_THERMOMETER_H

#include "thermometer.h"

#include <time.h>

class HangThermometer : public Thermometer
{
public:
    HangThermometer(timespec hang_time, double temperature);
    virtual double get_temperature() const;

private:
    timespec _hang_time;
    double _temperature;
};

#endif
