/* Exercise 2,
   safe_thermometer tests,
   Temmel Philipp
 */

#include <crash_thermometer.h>
#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>

#include <iostream>

#include "safe_thermometer.h"

using namespace std;

/** 
 Tests all 4 different thermometers.
*/
int main() {
  cout << "01: crash-thermometer-test:" << endl;
  {
    try {
	  SafeThermometer safeThermometer(new CrashThermometer());
	  cout << safeThermometer.get_temperature() << endl;
    } catch (ThermometerException& e) {
	  cerr << e.what() << endl;
    }
  }

  cout << "02: fixed-thermometer-test:" << endl;
  {
    try {
	  SafeThermometer safeThermometer(new FixedThermometer(36.5));
	  cout << safeThermometer.get_temperature() << endl;
    } catch (ThermometerException& e) {
	  cerr << e.what() << endl;
    }
  }

  cout << "03: hang-thermometer-test:" << endl;
  {
    try {
      timespec hangTime = {3,0};
	  SafeThermometer safeThermometer(new HangThermometer(hangTime, 37.4));

	  cout << "Measured temperature is delayed by " << hangTime.tv_sec << " sec and " << hangTime.tv_nsec << " nano-sec." << endl;
	  cout << "The measured value after the delay is: " << safeThermometer.get_temperature() << endl;
    } catch (ThermometerException& e) {
	  cerr << e.what() << endl;
    }
  }

  cout << "04: random-thermometer-test:" << endl;
  {
    try {
	  SafeThermometer safeThermometer(new RandomThermometer());
	  cout << "First randomly generated and measured temperature = " << safeThermometer.get_temperature() << endl;
	  cout << "Second randomly generated and measured temperature = " << safeThermometer.get_temperature() << endl;
	  cout << "Third randomly generated and measured temperature = " << safeThermometer.get_temperature() << endl;
	  cout << "Fourth randomly generated and measured temperature = " << safeThermometer.get_temperature() << endl;
    } catch (ThermometerException& e) {
	  cerr << e.what() << endl;
    }
  }

  /* Exit main-function. */
  return 0;
}