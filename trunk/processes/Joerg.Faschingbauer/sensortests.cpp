#include <hang_thermometer.h>

#include <iostream>

using namespace std;

int main()
{
    timespec hang_time = {10,0};
    
    HangThermometer hth(hang_time, 36.5);
    cout << "Temperature will come after " << hang_time.tv_sec << " seconds "
        "and " << hang_time.tv_nsec << " nanoseconds ..." << endl;
    cout << "Well, here we go: " << hth.get_temperature() << endl;

    return 0;
}
