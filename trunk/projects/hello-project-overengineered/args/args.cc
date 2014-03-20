#include "hello_args.h"

#include <hello_output.h>

void hello_args(int argc, char** argv)
{
    if (argc > 1) {
        for (int i=1; i<argc; i++)
            cout << argv[i] << endl;
    }
    else {
        cerr << "No arguments given" << endl;
    }
}
