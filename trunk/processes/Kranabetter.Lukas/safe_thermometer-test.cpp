#include <iostream>
#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>

#include "safe_thermometer.h"

using namespace std;

/**
 * Test the safe thermometer wrapper with various kinds of thermometers<br>
 *
 * @author Lukas Kranabetter
 */
int main()
{
	cout << "FixedThermometer" << endl;
	{
		try
		{
			SafeThermometer safe_thermometer(new FixedThermometer(36.5));
			cout << safe_thermometer.get_temperature() << endl;
		}
		catch(ThermometerException& ex)
		{
			cerr << ex.what() << endl;
		}
	}

	cout << "RandomThermometer" << endl;
	{
		try
		{
			SafeThermometer safe_thermometer(new RandomThermometer());
			cout << safe_thermometer.get_temperature() << endl;
		}
		catch(ThermometerException& ex)
		{
			cerr << ex.what() << endl;
		}
	}

	cout << "HangThermometer" << endl;
	{
		try
		{
			timespec delay = {2, 0};
			// Test in time
			SafeThermometer safe_thermometer(new HangThermometer(delay, 36.5), 3);
			cout << safe_thermometer.get_temperature() << endl;
			// Test timeout
			SafeThermometer safe_thermometer_timeout(new HangThermometer(delay, 36.5), 1);
			cout << safe_thermometer_timeout.get_temperature() << endl;
		}
		catch(ThermometerException& ex)
		{
			cerr << ex.what() << endl;
		}
	}

	cout << "CrashThermometer" << endl;
	{
		try
		{
			SafeThermometer safe_thermometer(new CrashThermometer());
			cout << safe_thermometer.get_temperature() << endl;
		}
		catch(ThermometerException& ex)
		{
			cerr << ex.what() << endl;
		}
	}

	return 0;
}
