# for all compilations in this directory, we look in these directories
# for included files. ${CMAKE_SOURCE_DIR} is the project's root
# directory (the one containing the CMakeLists.txt file with the
# PROJECT() declaration.)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/args
    ${CMAKE_SOURCE_DIR}/environ
)


# we build an executable here, out of one single source file.

ADD_EXECUTABLE(
    hello

    hello.cc)


# the hello is not standalone. it contain open refenences to a few
# symbols which are defined in the libraries we give here.

TARGET_LINK_LIBRARIES(
    hello

    hello_args
    hello_environ
)
