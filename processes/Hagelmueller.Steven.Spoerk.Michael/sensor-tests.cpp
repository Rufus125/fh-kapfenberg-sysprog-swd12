#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>
#include "safe_thermometer.h"

#include <iostream>

using namespace std;

int main()
{
    cout << "--- FixedThermometer" << endl;
    {
        FixedThermometer ft(36.5);
	SafeThermometer th(ft);
	try
	{
        	cout << th.get_temperature() << endl;
	}
	catch(ThermometerException& ex)
	{
		cerr << ex.what() << endl;
	}
    }

    cout << "--- RandomThermometer" << endl;
    {
        RandomThermometer rt;
	SafeThermometer th(rt);
	try
	{
		cout << "one random temperature: " << th.get_temperature() << endl;
		cout << "another random temperature: " << th.get_temperature() << endl;
		cout << "yet another random temperature: " << th.get_temperature() << endl;
	}
	catch(ThermometerException& ex)
	{
		cerr << ex.what() << endl;
	}    
    }
        
    cout << "--- HangThermometer" << endl;
    {
        timespec hang_time = {5,0};
        HangThermometer ht(hang_time, 36.5);
	SafeThermometer th(ht);
	try
	{
		cout << "Temperature will come after " << hang_time.tv_sec << " seconds "
		    "and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
		cout << "Well, here we go: " << th.get_temperature() << endl;
	}
	catch(ThermometerException& ex)
	{
		cerr << ex.what() << endl;
	}
    }
        
    cout << "--- CrashThermometer" << endl;
    {
        CrashThermometer ct;
	SafeThermometer th(ct);
	try
	{
		cout << "And now for something completely different: " << flush;
		cout << th.get_temperature() << endl;
	}
	catch(ThermometerException& ex)
	{
		cerr << ex.what() << endl;
	}
    }
        
    return 0;
}
