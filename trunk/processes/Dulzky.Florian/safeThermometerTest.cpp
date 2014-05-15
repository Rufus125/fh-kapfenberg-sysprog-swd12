#include "safeThermometer.h"
#include "fixed_thermometer.h"
#include "hang_thermometer.h"
#include "random_thermometer.h"
#include "crash_thermometer.h"

using namespace std;

int main(void){

	cout << "FixedThermometer:" << endl;
	{
		SafeThermometer st(new FixedThermometer (36.5));
    	cout << st.get_temperature() << endl;
	}
	
	cout << "RandomThermo:" << endl;
	{
		SafeThermometer st(new RandomThermometer());
		cout << st.get_temperature() << endl;
		cout << st.get_temperature() << endl;
		cout << st.get_temperature() << endl;
	}
	
	cout << "HangThermo:" << endl;
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
			
	cout << "CrashThermo:" << endl;
	{
		SafeThermometer st(new CrashThermometer());
		cout << st.get_temperature() << endl;
	}

	return 0;
}
