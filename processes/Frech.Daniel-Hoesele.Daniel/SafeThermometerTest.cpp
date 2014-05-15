// Daniel Hoesele - Daniel Frech - SWD12

#include "SafeThermometer.h"
#include "../sensors/fixed_thermometer.h"
#include "../sensors/hang_thermometer.h"
#include "../sensors/random_thermometer.h"
#include "../sensors/crash_thermometer.h"

using namespace std;

int main()
{
	//SafeFixedThermoTest:
    cout << "--- FixedThermometer" << endl;
    try
    {
		SafeThermometer th(new FixedThermometer (36.5));
    	cout << th.get_temperature() << endl;
    }
    catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	//SafeRandomThermoTest:
    cout << "--- RandomThermometer" << endl;
    try
    {
        SafeThermometer th(new RandomThermometer());
        cout << "one random temperature: " << th.get_temperature() << endl;
        cout << "another random temperature: " << th.get_temperature() << endl;
        cout << "yet another random temperature: " << th.get_temperature() << endl;
    }
    catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

    //SafeHangThermoTest:
    cout << "--- HangThermometer" << endl;
    try
    {
        timespec hang_time = {5,0};
        SafeThermometer th(new HangThermometer(hang_time, 36.5));
        cout << "Temperature will come after " << hang_time.tv_sec << " seconds "
            "and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
        cout << "Well, here we go: " << th.get_temperature() << endl;
    }
    catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

    //SafeCrashThermoTest:
    cout << "--- CrashThermometer" << endl;
    try
    {
        SafeThermometer th(new CrashThermometer());
        cout << "And now something completely different: " << flush;
        cout << th.get_temperature() << endl;
    }
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

    return 0;
}
