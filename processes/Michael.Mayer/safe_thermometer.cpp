#include "safe_thermometer.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

static void write_all(int fd, const char *data, size_t len);

SafeThermometer::SafeThermometer(unsigned int timeout, Thermometer* thermometer):
    _timeout(timeout)
{
    _thermometer = thermometer;
}
    
double SafeThermometer::get_temperature() const
{
    double temperature;
        
    int pipe_fd[2];

    int err = pipe(pipe_fd);
    if (err == -1) {
        perror("pipe creation");
        abort();
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork process");
        abort();
    }
    else if (pid == 0) {
        // child. close parent's end.
        close(pipe_fd[0]);
        
        // start alarm for possible hanging thermometer
        alarm(_timeout);
        // read temperature from instable thermometer
        double inst_temp = _thermometer->get_temperature();        
        // write temperature into pipe
        stringstream strstream;
        strstream << inst_temp;
        string message = strstream.str();
        write_all(pipe_fd[1], message.c_str(), message.size());
        
        // done; close pipe so parent can realize we are done
        close(pipe_fd[1]);
        // important: do not escape into parent code        
        exit(0);
    }
    else {    
        // parent. close child's end.
        close(pipe_fd[1]);
        string message;
        while(true) {
            char readbuf[2];
            ssize_t nread = read(pipe_fd[0], readbuf, sizeof(readbuf));
            if (nread > 0) {
                message.append(readbuf);
            }
            else if (nread == 0) {
                temperature = strtod(message.c_str(), NULL);
                break;
            }
            else {
                perror("read");
                abort();
            }
        }
        // inspect child process.
        int child_status;
        pid_t wait_status = waitpid(pid, &child_status, 0);
        if(!WIFEXITED(child_status)) {
            if(WIFSIGNALED(child_status)) {
                stringstream message_stream;
                message_stream << "Instable thermometer died due to signal: " << WTERMSIG(child_status) << endl;
                throw ThermometerException(message_stream.str());
            }
            else {
                throw ThermometerException("Instable thermometer died unreasonable");
            }
        }        
    }
    return temperature;
}

static void write_all(int fd, const char *data, size_t len)
{
    while (len != 0) {
        ssize_t written = write(fd, data, len);
        if (written == -1) {
            perror("write");
            abort();
        }
        data += written;
        len -= written;
    }
}

