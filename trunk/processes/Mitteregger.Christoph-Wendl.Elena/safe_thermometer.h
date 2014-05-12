#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"

class SafeThermometer : public Thermometer
{
  public:
    SafeThermometer(Thermometer* different_thermometers);
    virtual ~SafeThermometer();
    virtual double get_temperature() const;

  private:
    Thermometer* unstable_thermometer;
    unsigned const static int alarm_time = 10;
};
#endif
