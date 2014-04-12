#include "thermometer.h"
#include <unistd.h>
#include <string>

class SafeThermometer : public Thermometer
{
private:
	Thermometer * unstableThermometer;
	unsigned long timeout;
public:
	~SafeThermometer();
	SafeThermometer(Thermometer* unstableThermometer, unsigned long timeout = 6);
	virtual double get_temperature() const;
};
