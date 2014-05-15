#include "safeThermometer.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

SafeThermometer::SafeThermometer(Thermometer* unstableThermometer, unsigned int timeout)
  :_unstableThermometer(unstableThermometer)
  ,_timeout(timeout)
{

}

SafeThermometer::~SafeThermometer()
{
  delete _unstableThermometer;
}

double SafeThermometer::get_temperature() const
{
  int pipefd[2];

  // Pipe erstellen mit Zeiger auf Anfangspunkt und Endpunkt (pipefd[0] bzw. pipefd[1])
  int err = pipe(pipefd);
  if (err == -1)
  {
    perror("Pipe konnte nicht erstellt werden!");
  }

  double temperature = 0.0;
  char temperature_chars[64];

  // Prozess forken
  pid_t pid = fork();
  if (pid == -1)
  {
    throw ThermometerException("Fehler beim Forken");
  }
  else if (pid == 0)
  {
    close(pipefd[0]);

    alarm(_timeout);
    temperature = _unstableThermometer->get_temperature();
    sprintf(temperature_chars, "%f", temperature);
  
    ssize_t numberWritten = write(pipefd[1], temperature_chars, (strlen(temperature_chars) + 1) * sizeof(char));
    if (numberWritten == -1)
    {
      abort();
    }

    close(pipefd[1]);  
    exit(EXIT_SUCCESS);
  }
  else
  {
    close(pipefd[1]);
    
    int status = 0;
    waitpid(pid, &status, 0);
    
    if (!WIFEXITED(status))
    {
      throw ThermometerException("Timeout oder Crash des Thermometers");
      close(pipefd[0]);
    }

    ssize_t numberRead = read(pipefd[0], temperature_chars, sizeof(temperature_chars));
    close(pipefd[0]);
    
    if (numberRead <= 0)
    {
      throw ThermometerException("Konnte Temperatur nicht abfragen");
    }
    else
    {
      temperature = atof(temperature_chars);
    }
    }  
  
  return temperature;
}


