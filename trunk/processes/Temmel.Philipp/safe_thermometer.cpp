/* Exercise 2,
   safe_thermometer program,
   Temmel Philipp
 */

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

using namespace std;

/** constructor */
SafeThermometer::SafeThermometer(Thermometer* unstableThermometer, unsigned int crashTime) {
  _unstableThermometer = unstableThermometer;
  _crashTime = crashTime;
}

/** destructor */
SafeThermometer::~SafeThermometer() {}

/** Returns the measured sensor temperature by forking a new process (child). */
double SafeThermometer::get_temperature() const {
  /* define variables */
  int pipeFd[2];
  double measuredTemperature = 0.0;

  /* Open pipe and check if successful. */
  if (pipe(pipeFd) == -1) {
    throw ThermometerException("Failed to open pipe!");
  }

  /* Fork the process (i.e. create child-process). */
  pid_t pid = fork();

  if (pid == -1) {
    throw ThermometerException("Failed to fork a new child process!");
  } else if (pid == 0) { // child-process
    /* Close read-fd (always close not needed ends prior to anything else). */
    close(pipeFd[0]);

    /* Define the timer, when the alarm should set of. */
    alarm(_crashTime);

    /* Retrieve temperature from an unsafe thermometer. */
    measuredTemperature = _unstableThermometer->get_temperature();

    /* Write the measured temperature into the pipe by using the write-fd. */
    ssize_t pipeWrite = write(pipeFd[1], &measuredTemperature, sizeof(measuredTemperature));

    /* Check if the measured temperature has been written to the pipe successfully. */
    if(pipeWrite == -1) {
      /* Close the write-fd prior throwing the exception so that the parent-process gets notified without any delay. */
      close(pipeFd[1]);

      throw new ThermometerException("Child-process: Failed to write measured temperature into pipe!");
    }
    
    /* Close write-fd (so that parent-process realises that we have finished our job). */
    close(pipeFd[1]);

    /* Exit the child-process (successful). */
    exit(EXIT_SUCCESS);
  } else { // parent-process
    /* Close write-fd (always close not needed ends prior to anything else). */
    close(pipeFd[1]);

    /* Initialise status. */
    int status = 0;

    /* Check if thermometer status could be retrieved successfully. */
    if (waitpid(pid, &status, 0) == -1) {
      /* Close the read-fd prior throwing the exception so that the child-process gets notified without any delay. */
      close(pipeFd[0]);

      throw ThermometerException("Parent-process: Failed to retrieve thermometer status!");
    }

    /* Check if the sensor crashed (alarm went of). */
    if(!WIFEXITED(status)) {
      /* Close the read-fd prior throwing the exception so that the child-process gets notified without any delay. */
      close(pipeFd[0]);

      throw ThermometerException("Parent-process: The unsafe thermometer crashed!");
    }

    /* Read the measured temperature from the pipe. */
    ssize_t pipeRead = read(pipeFd[0], &measuredTemperature, sizeof(measuredTemperature));

    /* Check if the measured temperature was read successfully from the pipe. */
    if (pipeRead <= 0) {
      /* Close the read-fd prior throwing the exception so that the child-process gets notified without any delay. */
      close(pipeFd[0]);

      throw ThermometerException("Parent-process: Failed to read the measured temperature from the pipe!");
    }

    /* Close read-fd after successfully reading the measured temperature from the pipe. */
    close(pipeFd[0]);
  }

  /* Return the measured temperature. */
  return measuredTemperature;
}
