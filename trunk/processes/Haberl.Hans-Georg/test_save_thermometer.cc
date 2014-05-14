#include "fixed_thermometer.h"
#include "hang_thermometer.h"
#include "random_thermometer.h"
#include "save_thermometer.h"
#include "crash_thermometer.h"
#include <iostream>

using namespace std;

int main() {

	cout << "FixedThermometer:" << endl;
	try {
		SafeThermometer thermometer (new FixedThermometer(0.0));
		cout << thermometer.get_temperature() << endl;
	} catch (ThermometerException& ex) {
		cerr << ex.what() << endl;
	}

	cout << "RandomThermometer:" << endl;
	try {
		SafeThermometer thermometer (new RandomThermometer());
		cout << thermometer.get_temperature() << endl;
	} catch (ThermometerException& ex) {
		cerr << ex.what() << endl;
	}

	cout << "HangThermometer:" << endl;
	try {
		timespec hang_time = {3,0};
		SafeThermometer thermometer (new HangThermometer(hang_time, -900.9));
		cout << thermometer.get_temperature() << endl;
	} catch (ThermometerException& ex) {
		cerr << ex.what() << endl;
	}

	cout << "CrashThermometer:" << endl;
	try {
		SafeThermometer thermometer (new CrashThermometer());
		cout << thermometer.get_temperature() << endl;
	} catch (ThermometerException& ex) {
		cerr << ex.what() << endl;
	}
}
