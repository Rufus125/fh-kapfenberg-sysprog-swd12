#include <iostream>
#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>

#include "safe_thermometer.h"

using namespace std;

int main() {
	cout << "FixedThermometer" << endl;
	{
		try {
			SafeThermometer safeTh(new FixedThermometer(36.5));
			cout << safeTh.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		}
	}

	cout << "RandomThermometer" << endl;
	{
		try {
			SafeThermometer safeTh(new RandomThermometer());
			cout << safeTh.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		}
	}

	cout << "HangThermometer" << endl;
	{
		try {
			timespec hang_time = { 5, 0 };
			SafeThermometer safeTh(new HangThermometer(hang_time, 36.5), 3);
			cout << safeTh.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		}
	}

	cout << "CrashThermometer" << endl;
	{
		try {
			SafeThermometer safeTh(new CrashThermometer());
			cout << safeTh.get_temperature() << endl;
		} catch (ThermometerException& ex) {
			cerr << ex.what() << endl;
		}
	}

	return 0;
}
