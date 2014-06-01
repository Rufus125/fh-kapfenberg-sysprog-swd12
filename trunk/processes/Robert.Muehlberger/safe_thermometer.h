#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"
/*
 * SafeThermomenter inherit Thermometer
 */
class SafeThermometer : public Thermometer {
	
public:
	// Constructor
	SafeThermometer(Thermometer* saveThermometer, int timeout = 3);
	// Deconstructor
	virtual ~SafeThermometer();
	// Return temperature is implent by each single thermometer 
	// Delegation
    virtual double get_temperature() const; 
    
private:
	// Hold instance of a thermometer 
	Thermometer* sandboxThermometer;
	// To set alram clock
	int timeout;

};

#endif
