#include "hello_output.h"

#include <iostream>

using namespace std;

void hello_stdout(const std::string& str)
{
    cout << str << '\n';
}

void hello_stderr(const std::string& str)
{
    cerr << str << '\n';
}
