#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>
#include "safe_thermometer.h"

#include <iostream>

using namespace std;
/**
 * Program produce a sandbox called SafeThermometer.
 * This sandbox will hold a thermometer
 * If the thermometer is a broken one he will throw an exeption
 * 
 */
int main() {

	
	cout << "--- Fixedthermometer in sandbox" << endl; {
		try {
			SafeThermometer sandbox(new FixedThermometer(36.5));
			cout << sandbox.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		} // try catch block
	} // cout

	cout << "--- Randomthermometer in sandbox" << endl; {
		try {
			SafeThermometer sandbox(new RandomThermometer());
			cout << "one random temperature: " << sandbox.get_temperature() << endl;
			cout << "another random temperature: " << sandbox.get_temperature() << endl;
			cout << "yet another random temperature: " << sandbox.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		} // try catch block
	} // cout

	cout << "--- Hangthermometer in sandbox" << endl; {
		try {
			timespec hang_time = {5,0};
			SafeThermometer sandbox(new HangThermometer(hang_time, 36.5));
			cout << "temperature will come after " << hang_time.tv_sec << " seconds "
			"and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
			cout << "well, here we go: " << sandbox.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		} // try catch block	
	} // cout
        
	cout << "--- Crashthermometer in sandbox" << endl; {
		try {
			SafeThermometer sandbox(new CrashThermometer());
			cout << "and now for something completely different: " << flush;
			cout << sandbox.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		} // try catch block	
	} // cout
        
	return 0;
} // main
