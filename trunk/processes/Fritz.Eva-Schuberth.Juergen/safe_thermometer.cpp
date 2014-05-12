#include "safe_thermometer.h"
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// Konstruktor
SafeThermometer::SafeThermometer(Thermometer* unstable_thermometer)
	:_unstable_thermometer(unstable_thermometer)
{

}

// Destruktor
SafeThermometer::~SafeThermometer()
{
	delete _unstable_thermometer;
}

// Methode zur Temperaturabfrage
double SafeThermometer::get_temperature() const
{
	// Pipe zur IPC anlegen
    int pipe_fd[2];


    int err = pipe(pipe_fd); // -> man
    if (err == -1) {
        perror("pipe");
        abort();
    }

    // Prozess zur Abfrage wegforken
    pid_t pid = fork(); // -> man
    if (pid == -1) {
        perror("fork");
        abort();
    }
    else if (pid == 0) {
    	// Kindprozess
        // child. close parent's end.

    	alarm(3);
        close(pipe_fd[0]);

        double temp = _unstable_thermometer->get_temperature();
        write (pipe_fd[1], (void*)&temp, sizeof(double));


        // done; close pipe so parent can realize we are done
        close(pipe_fd[1]);
        // important: do not escape into parent code
        exit(0);
    }
    else {
        // Elternprozess
    	// parent. close child's end.
        close(pipe_fd[1]);

        int status = 0;
        pid_t result = waitpid(pid, &status, 0);

        if (!WIFEXITED(status)) // normal beendet
        {
        	close(pipe_fd[0]);
        	throw ThermometerException("Keine Zeit um länger zu warten!");
        }

        double temp = 2;
        ssize_t nread = read(pipe_fd[0], (void*)&temp, sizeof(double));
        close(pipe_fd[0]);

        if (nread <= 0)
        {
        	throw ThermometerException("Fehler");
        }

        return temp;




    }

	return 0.0;
}

