#include <random_thermometer.h>
#include <hang_thermometer.h>
#include <fixed_thermometer.h>
#include <crash_thermometer.h>
#include "safe_thermometer.h"

#include <iostream>

using namespace std;

int main()
{
  cout << "--- FixedThermometer" << endl;
  {
    try
    {
      SafeThermometer th(new FixedThermometer(36.5));
      //SafeThermometer th = new FixedThermometer(36.5);
      cout << th.get_temperature() << endl;
    }
    catch (ThermometerException& ex)
    {
      cerr << ex.what() << endl;
    }
  }

  cout << "--- RandomThermometer" << endl;
  {
    try
    {
      SafeThermometer th(new RandomThermometer());
      cout << "one random temperature: " << th.get_temperature() << endl;
      cout << "another random temperature: " << th.get_temperature() << endl;
      cout << "yet another random temperature: " << th.get_temperature() << endl;
    }
    catch (ThermometerException& ex)
    {
      cerr << ex.what() << endl;
    }
  }

  cout << "--- HangThermometer" << endl;
  {
    try
    {
      timespec hang_time = {5,0};
      SafeThermometer th(new HangThermometer(hang_time, 36.5));
      //SafeThermometer th = new HangThermometer(hang_time, 36.5);
      cout << "Temperature will come after " << hang_time.tv_sec << " seconds "
            "and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
      cout << "Well, here we go: " << th.get_temperature() << endl;
    }
    catch (ThermometerException& ex)
    {
      cerr << ex.what() << endl;
    }
  }

    cout << "--- CrashThermometer" << endl;
    {
      try
      {
        SafeThermometer th(new CrashThermometer());
        cout << "And now for something completely different: " << flush;
        cout << th.get_temperature() << endl;
      }
      catch (ThermometerException& ex)
      {
        cerr << ex.what() << endl;
      }
    }

  return 0;


}
