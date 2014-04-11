#include "safe_thermometer.h"

SafeThermometer::SafeThermometer(Thermometer* unsafe_thermometer)
	:_unsafe_thermometer(unsafe_thermometer)
{

}

double SafeThermometer::get_temperature() const
{
	return _unsafe_thermometer->get_temperature();
}
