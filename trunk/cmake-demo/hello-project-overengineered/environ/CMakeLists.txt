# for all compilations in this directory, we look in these directories
# for included files. ${CMAKE_SOURCE_DIR} is the project's root
# directory (the one containing the CMakeLists.txt file with the
# PROJECT() declaration.)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/output
)


# we build a library, libhello_environ.a (or libhello_environ.so, if
# we build shared libraries). this library contains the files
# hello_environ.h and hello_environ.cc.

ADD_LIBRARY(
    hello_environ
    
    hello_environ.h
    hello_environ.cc)


# the hello_environ library is not self contained, but rather brings
# in a couple of open references. these are resolved by another
# library, hello_output.

TARGET_LINK_LIBRARIES(
    hello_environ

    hello_output
)
