#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>
#include "safe_thermometer.h"
#include <iostream>
using namespace std;

int main()
{
		SafeThermometer th(new FixedThermometer(24));
		cout << th.get_temperature() << endl;
}
