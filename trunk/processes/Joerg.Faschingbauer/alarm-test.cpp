#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    unsigned int alarm_time = 2;
    cout << "Scheduling alarm signal in " << alarm_time << " seconds" << endl;
    alarm(alarm_time);
    pause();
    return 0;
}
