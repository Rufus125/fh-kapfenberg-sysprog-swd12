#include "safe_thermo.h"
#include "fixed_thermometer.h"
#include "hang_thermometer.h"
#include "random_thermometer.h"
#include "crash_thermometer.h"

using namespace std;

int main(void){

	cout << "--- FixedThermometer" << endl;
	try
	{
		SafeThermometer st(new FixedThermometer (36.5));
    	cout << st.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	cout << "--- RandomThermometer" << endl;
	try
	{
		SafeThermometer st(new RandomThermometer());
    	cout << "one random temperature: " << st.get_temperature() << endl;
        cout << "another random temperature: " << st.get_temperature() << endl;
        cout << "yet another random temperature: " << st.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	cout << "--- HangThermometer" << endl;
	try
	{
		timespec hang_time = {5,0};
		SafeThermometer st(new HangThermometer(hang_time, 13.37));
        cout << "Temperature will come after " << hang_time.tv_sec << " seconds "
            "and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
        cout << "Well, here we go: " << st.get_temperature() << endl;

		timespec hang_too_long = {8,0};
		SafeThermometer stTimeoutIncreased(new HangThermometer(hang_too_long, 47.11), 10); // timeout bigger than longer hang time
        cout << "Temperature will come after " << hang_too_long.tv_sec << " seconds "
            "and " << hang_too_long.tv_nsec << " nanoseconds ... " << endl;
		cout << "Timeout set to 8!" << endl;
        cout << "Well, here we go: " << stTimeoutIncreased.get_temperature() << endl;
		
		SafeThermometer stTimeoutReached(new HangThermometer(hang_too_long, 47.11));
        cout << "Temperature will come after " << hang_too_long.tv_sec << " seconds "
            "and " << hang_too_long.tv_nsec << " nanoseconds ... But now the twist: our timeout is set to 6!" << endl;
        cout << "Well, here we go: " << stTimeoutReached.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	cout << "--- CrashThermometer" << endl;
	try
	{
		SafeThermometer st(new CrashThermometer());
    	cout << "And now for something completely different: " << flush;
		cout << st.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	return 0;
}
