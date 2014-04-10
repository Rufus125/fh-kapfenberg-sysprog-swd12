#include <fixed_thermometer.h>
#include <hang_thermometer.h>
#include <random_thermometer.h>
#include <crash_thermometer.h>

#include <iostream>

using namespace std;

int main()
{
    cout << "--- FixedThermometer" << endl;
    {
        FixedThermometer th(36.5);
        cout << th.get_temperature() << endl;
    }

    cout << "--- RandomThermometer" << endl;
    {
        RandomThermometer th;
        cout << "one random temperature: " << th.get_temperature() << endl;
        cout << "another random temperature: " << th.get_temperature() << endl;
        cout << "yet another random temperature: " << th.get_temperature() << endl;
    }
        
    cout << "--- HangThermometer" << endl;
    {
        timespec hang_time = {5,0};
        HangThermometer th(hang_time, 36.5);
        cout << "Temperature will come after " << hang_time.tv_sec << " seconds "
            "and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
        cout << "Well, here we go: " << th.get_temperature() << endl;
    }
        
    cout << "--- CrashThermometer" << endl;
    {
        CrashThermometer th;
        cout << "And now for something completely different: " << flush;
        cout << th.get_temperature() << endl;
    }
        
    return 0;
}
