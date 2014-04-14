#ifndef SAVETHERMOMETER_H
#define SAVETHERMOMETER_H

#include "thermometer.h"

class SafeThermometer :Thermometer 
{
public:
  // Constructor for class X
  SafeThermometer(Thermometer* thermometer);
  
  virtual double get_temperature() const = 0;
      
  // Destructor for class X
  ~SafeThermometer();
};

#endif
