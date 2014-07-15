INCLUDE_DIRECTORIES(
    ../lib
)

ADD_EXECUTABLE(
    server
    server.cpp

)
TARGET_LINK_LIBRARIES(
    server
    lib
)
