INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    Joerg.Faschingbauer.sensortests
    sensortests.cpp
)
TARGET_LINK_LIBRARIES(
    Joerg.Faschingbauer.sensortests
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
