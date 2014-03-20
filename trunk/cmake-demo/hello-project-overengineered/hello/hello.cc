#include <hello_args.h>
#include <hello_environ.h>

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    // print the program's arguments
    hello_args(argc, argv);

    // print the program's environment variables.
    hello_environ();

    return 0;
}
