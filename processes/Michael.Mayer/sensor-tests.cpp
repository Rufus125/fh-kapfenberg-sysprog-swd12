#include "safe_thermometer.h"

#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <crash_thermometer.h>

#include <time.h>
#include <iostream>
#include <exception>

static void secure_thermometer_call(Thermometer* th);

using namespace std;

int main()
{
    //---- Safe FixedThermometer ----
    {
        // create an instable thermometer
        FixedThermometer fth(36.5);
        // create a safe thermometer with 2 seconds timeout
        SafeThermometer th(2, &fth);
        secure_thermometer_call(&th);
    }
    
    //---- Safe HangThermometer ----
    {
        // create an instable thermometer
        timespec hang_time = {30,0};
        HangThermometer hth(hang_time, 36.6);
        // create a safe thermometer with 2 seconds timeout
        SafeThermometer th(2, &hth);
        secure_thermometer_call(&th);
    }
    
    //---- Safe CrashThermometer ----
    {
        // create an instable thermometer
        CrashThermometer cth;
        // create a safe thermometer with 2 seconds timeout
        SafeThermometer th(2, &cth);
        secure_thermometer_call(&th);
    }
    
    
    return 0;
}


static void secure_thermometer_call(Thermometer* th)
{
    try {
        cout << "Temperature: " << th->get_temperature() << endl;
    } catch(ThermometerException& e) {
        cerr << "Thermometer exception: " << e.what() << endl;
    }

}

