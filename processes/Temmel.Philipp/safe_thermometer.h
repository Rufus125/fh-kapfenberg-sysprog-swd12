/* header guard */
#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

/* includes */
#include "thermometer.h"

/**
 * SafeThermometer class which is a Thermometer, holds an unstable thermometer and uses this one to measure the temperature 'safely' in another process.
 */
class SafeThermometer : public Thermometer {
  public:
    SafeThermometer(Thermometer* unstableThermometer, unsigned int crashTime = 5);
    virtual ~SafeThermometer();
    virtual double get_temperature() const;

  private:
    Thermometer* _unstableThermometer;
    unsigned int _crashTime;
};

#endif