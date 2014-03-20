# we build a library, libhello_output.a (or libhello_output.so, if we
# build shared libraries). this library contains the files
# hello_output.h and hello_output.cc.

ADD_LIBRARY(
    hello_output

    hello_output.h
    hello_output.cc)
