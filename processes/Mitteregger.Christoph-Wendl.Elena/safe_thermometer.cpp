
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "safe_thermometer.h"
#include "thermometer.h"

#define ERROR -1
using namespace std;

SafeThermometer::SafeThermometer(Thermometer* thermometer)
{
  unstable_thermometer = thermometer;
}

SafeThermometer::~SafeThermometer()
{
 // delete _unstable_thermometer;
}

double SafeThermometer::get_temperature() const
{
  int pipe_fd[2];

  if (pipe(pipe_fd) == ERROR)
  {
    throw ThermometerException("pipe could not be opened");
  }

  double temperature = 0.0;

  //getting new pid with fork
  pid_t pid = fork();

  if (pid == ERROR)
  {
    throw ThermometerException("unable to fork new process");
  }
  else if (pid == 0)//child
  {

    //close readFileDescriptor - parents end
    close(pipe_fd[0]); //close parents end

    //set the alarm time
    alarm(alarm_time);

    //get the temperature
    temperature = unstable_thermometer->get_temperature();

    //writing into pipe
    ssize_t pwrite = write(pipe_fd[1], &temperature, sizeof(temperature));

    if (pwrite == ERROR)
    {
      close(pipe_fd[1]);
      abort();
    }
    //close writeFileDescriptor - parent can realize that done
    close(pipe_fd[1]);
    exit(0);
   }
   else//parent
   {
     //close writeFileDescriptor - childs end
     close(pipe_fd[1]);

     int status = 0;

     if (waitpid(pid, &status, 0) == ERROR)
     {
      close(pipe_fd[0]);
      throw ThermometerException("could not query thermometer state");
     }

     if(!WIFEXITED(status))
     {
       close(pipe_fd[0]);
       throw ThermometerException("sensor crashed or timed out");
     }

     //reading from pipe
     ssize_t pread = read(pipe_fd[0], &temperature, sizeof(temperature));

     if (pread == 0)
     {
       cerr << "\n<<< END OF INPUT" << endl;
       //break;
     }
     else if (pread < 0)
     {
       close(pipe_fd[0]);
       throw ThermometerException("an error happened while reading temperature");
     }
     //close readFileDescriptor
     close(pipe_fd[0]);
   }
   return temperature;

}
