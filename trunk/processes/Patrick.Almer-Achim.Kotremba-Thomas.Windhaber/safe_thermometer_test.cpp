#include "safe_thermometer.h"
#include "fixed_thermometer.h"
#include "hang_thermometer.h"
#include "random_thermometer.h"
#include "crash_thermometer.h"

using namespace std;

int main(void){

	//cout << "--- FixedThermometer" << endl;
	try
	{
		SafeThermometer st(new FixedThermometer (36.5));
    	cout << st.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	//cout << "--- RandomThermometer" << endl;
	try
	{
		SafeThermometer st(new RandomThermometer());
		cout << st.get_temperature() << endl;
		cout << st.get_temperature() << endl;
		cout << st.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	//cout << "--- HangThermometer" << endl;
	try
	{
		timespec hang_time = {5,0};
		SafeThermometer st(new HangThermometer(hang_time, 13.37));
        cout << st.get_temperature() << endl;

		timespec hang_too_long = {8,0};
		SafeThermometer stTimeoutIncreased(new HangThermometer(hang_too_long, 47.11), 10); // timeout bigger than longer hang time
        cout << stTimeoutIncreased.get_temperature() << endl;
		
		SafeThermometer stTimeoutReached(new HangThermometer(hang_too_long, 47.11));
        cout << stTimeoutReached.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	//cout << "--- CrashThermometer" << endl;
	try
	{
		SafeThermometer st(new CrashThermometer());
		cout << st.get_temperature() << endl;
	}
	catch(ThermometerException ex)
	{
		cerr << ex.what() << endl;
	}

	return 0;
}
