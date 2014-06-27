#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

int activate_gpio(int gpio_nr);
int gpio_is_active(int gpio_nr);
int gpio_on(int gpio_nr);
int gpio_off(int gpio_nr);

#endif