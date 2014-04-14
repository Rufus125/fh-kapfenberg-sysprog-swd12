#ifndef SAVETHERMOMETER_H
#define SAVETHERMOMETER_H

#include "thermometer.h"

class SafeThermometer : public Thermometer 
{
public:
	// Constructor for class X
	SafeThermometer(Thermometer* thermometer);
	
	// Destructor for class X
	virtual ~SafeThermometer();
	
	virtual double get_temperature() const;
	
private:
	Thermometer* thermometer;
};

#endif
