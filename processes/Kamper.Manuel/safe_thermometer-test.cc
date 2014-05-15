#include <iostream>
#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>

#include "safe_thermometer.h"

using namespace std;

//Thermometer mit verschiedenen Fehler-Termometern testen
int main()
{
	cout << ".) FixedThermometer" << endl;
	{
		try
		{
			SafeThermometer st(new FixedThermometer(32.5));
			cout << st.get_temperature() << endl;
		}
		catch(ThermometerException& e)
		{
			cerr << e.what() << endl;
		}
	}
	
	cout << ".) HangThermometer" << endl;
	{
		try
		{
			timespec waiter = {2, 0};
			//in time
			SafeThermometer st(new HangThermometer(waiter, 32.5), 3);
			cout << st.get_temperature() << endl;
			//timeout
			SafeThermometer st2(new HangThermometer(waiter, 32.5), 1);
			cout << st2.get_temperature() << endl;
		}
		catch(ThermometerException& e)
		{
			cerr << e.what() << endl;
		}
	}

	cout << ".) RandomThermometer" << endl;
	{
		try
		{
			SafeThermometer st(new RandomThermometer());
			cout << st.get_temperature() << endl;
		}
		catch(ThermometerException& e)
		{
			cerr << e.what() << endl;
		}
	}

	cout << ".) CrashThermometer" << endl;
	{
		try
		{
			SafeThermometer st(new CrashThermometer());
			cout << st.get_temperature() << endl;
		}
		catch(ThermometerException& e)
		{
			cerr << e.what() << endl;
		}
	}

	return 0;
}
