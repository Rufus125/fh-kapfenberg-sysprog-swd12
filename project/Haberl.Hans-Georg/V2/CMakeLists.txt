cmake_minimum_required(VERSION 2.8)
Project(communication)

ADD_EXECUTABLE(
    tetris_server
    server.cc
    communication.cc
)

ADD_EXECUTABLE(
    tetris_client
    client.cc
    communication.cc
)
