INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    Joerg.Faschingbauer.sensor-tests
    sensor-tests.cpp
)
TARGET_LINK_LIBRARIES(
    Joerg.Faschingbauer.sensor-tests
    sensors
)

ADD_EXECUTABLE(
    Joerg.Faschingbauer.alarm-test
    alarm-test.cpp
)
ADD_EXECUTABLE(
    Joerg.Faschingbauer.pipe-test
    pipe-test.cpp
)
