#include "hello_environ.h"

#include <hello_output.h>

#include <unistd.h>

void hello_environ()
{
    char **run = environ;
    while (*run != NULL) {
        hello_stdout(*run);
        run++;
    }
}
