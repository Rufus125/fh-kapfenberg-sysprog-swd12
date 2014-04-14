#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>
#include "safe_thermometer.h"
#include <iostream>
using namespace std;

void ExecThermometer(Thermometer* thermometerToExec);

int main()
{
	ExecThermometer(new FixedThermometer(21));
		
	timespec hang_time = {4,10};
	ExecThermometer(new HangThermometer(hang_time, 36.5));
	
	ExecThermometer(new RandomThermometer());
	
	ExecThermometer(new CrashThermometer());
}

void ExecThermometer(Thermometer* thermometerToExec)
{
	try
	{
		SafeThermometer th(thermometerToExec);
		cout << th.get_temperature() << endl;
	}
	catch (ThermometerException& ex)
	{
		cerr << ex.what() << endl;
	}	
}
