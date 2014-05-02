#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <thermometer.h>
#include <iostream>

class SafeThermometer : public Thermometer
{
public:
    SafeThermometer(Thermometer& thermometer);
    virtual double get_temperature() const;

private:
    struct sigaction action;
    static void sig_handler(int sig)
    {
      throw ThermometerException("Timeout");
    }

    Thermometer& thermometer;
};

#endif /* SAFE_THERMOMETER_H */
