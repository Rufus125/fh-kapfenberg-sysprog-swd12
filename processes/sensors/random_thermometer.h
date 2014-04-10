#ifndef RANDOM_THERMOMETER_H
#define RANDOM_THERMOMETER_H

#include "thermometer.h"

class RandomThermometer : public Thermometer
{
public:
    RandomThermometer();
    virtual double get_temperature() const;

private:
    int _random_fd;
};

#endif
