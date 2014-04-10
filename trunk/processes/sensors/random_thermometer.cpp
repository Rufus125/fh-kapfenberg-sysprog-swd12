#include "random_thermometer.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>

RandomThermometer::RandomThermometer()
{
    _random_fd = open("/dev/random", O_RDONLY);
    if (_random_fd == -1) {
        perror("open(\"/dev/random\")");
        abort();
    }
}

double RandomThermometer::get_temperature() const
{
    uint64_t number;
    int nread = read(_random_fd, &number, sizeof(number));
    if (nread == -1) {
        perror("read from /dev/random");
        abort();
    }
    if (nread != sizeof(uint64_t))
        abort();
    return (double)number;
}
