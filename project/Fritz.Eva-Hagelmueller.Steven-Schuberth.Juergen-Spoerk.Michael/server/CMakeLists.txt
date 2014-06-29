cmake_minimum_required(VERSION 2.8)

PROJECT(temp_server)

ADD_DEFINITIONS(-Wall)
set(CMAKE_EXE_LINKER_FLAGS "-Wall")

ADD_EXECUTABLE(temp_server tempserver.c)
