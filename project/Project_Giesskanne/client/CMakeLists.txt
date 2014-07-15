INCLUDE_DIRECTORIES(
    ../lib
)

ADD_EXECUTABLE(
    client
    client.cpp

)
TARGET_LINK_LIBRARIES(
    client
    lib
)
