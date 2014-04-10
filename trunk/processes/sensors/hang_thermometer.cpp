#include "hang_thermometer.h"

#include <stdlib.h>
#include <stdio.h>

HangThermometer::HangThermometer(
    timespec hang_time,
    double temperature)
: _hang_time(hang_time),
  _temperature(temperature) {}

double HangThermometer::get_temperature() const
{
    // hang around for the time we are supposed to
    int err = nanosleep(&_hang_time, NULL);
    if (err == -1) {
        perror("nanosleep");
        abort();
    }
    return _temperature;
}
