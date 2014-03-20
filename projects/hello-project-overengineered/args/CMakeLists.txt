# for all compilations in this directory, we look in these directories
# for included files. ${CMAKE_SOURCE_DIR} is the project's root
# directory (the one containing the CMakeLists.txt file with the
# PROJECT() declaration.)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/output
)


# we build a library, libhello_args.a (or libhello_args.so, if we
# build shared libraries). this library contains the files
# hello_args.h and hello_args.cc.

ADD_LIBRARY(
    hello_args
    
    hello_args.h
    hello_args.cc)


# the hello_args library is not self contained, but rather brings in a
# couple of open references. these are resolved by another library,
# hello_output.

TARGET_LINK_LIBRARIES(
    hello_args

    hello_output
)
