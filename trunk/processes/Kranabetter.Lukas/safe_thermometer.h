#ifndef SAFE_THERMOMETER_H
#define SAFE_THERMOMETER_H

#include "thermometer.h"

/**
 * Extend Thermometer class from sensors thermometer.h<br>
 * Get a unstable thermometer and measure temperature in a separated process<br>
 *
 * @author Lukas Kranabetter
 */
class SafeThermometer : public Thermometer
{
	public:
		SafeThermometer(Thermometer* unstable_thermometer, unsigned int timeout = 2);
		virtual double get_temperature() const;

	private:
		Thermometer* _unstable_thermometer;
		unsigned int _timeout;
};

#endif
