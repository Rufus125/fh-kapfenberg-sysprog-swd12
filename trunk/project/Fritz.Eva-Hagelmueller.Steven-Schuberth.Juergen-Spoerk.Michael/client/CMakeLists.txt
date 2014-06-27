cmake_minimum_required(VERSION 2.8)

# the project's name
PROJECT(temp_client)

ADD_DEFINITIONS(-Wall)
set(CMAKE_EXE_LINKER_FLAGS "-Wall")

# we build an executable out of a single source file
ADD_EXECUTABLE(temp_client temp_client.c network.c binary_temp.c gpio.c)
