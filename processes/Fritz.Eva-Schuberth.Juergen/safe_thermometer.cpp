#include "safe_thermometer.h"

SafeThermometer::SafeThermometer(Thermometer* unstable_thermometer)
	:_unstable_thermometer(unstable_thermometer)
{

}

SafeThermometer::~SafeThermometer()
{
	delete _unstable_thermometer;
}

double SafeThermometer::get_temperature() const
{
	return 0.0;
}
