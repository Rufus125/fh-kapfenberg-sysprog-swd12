#include "safe_thermometer.h"
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

SafeThermometer::SafeThermometer(Thermometer& th) : thermometer(th)
{

}

double SafeThermometer::get_temperature() const
{
    int pipe_fd[2];

    int err = pipe(pipe_fd);
    if (err == -1) {
        throw ThermometerException("pipe() failed");
    }

    pid_t pid = fork();
    if (pid == -1) 
    {
        throw ThermometerException("fork() failed");
    }
    else if (pid == 0) 
    {
      close(pipe_fd[0]);
      alarm(2);
      double temp = this->thermometer.get_temperature();
      write(pipe_fd[1], &temp, sizeof(double));
      exit(EXIT_SUCCESS);
    }
    else
    {
      close(pipe_fd[1]);
      int status;
      waitpid(pid, &status, 0);
      if(WIFEXITED(status))
      {
        double temp;
        read(pipe_fd[0], &temp, sizeof(double));
        return temp;
      }
      else
      {
        throw ThermometerException("could not receive temperature, child process failed");
      }
    }
}
