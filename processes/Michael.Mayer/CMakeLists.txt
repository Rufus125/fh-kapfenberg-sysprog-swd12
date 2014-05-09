INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors 
)

ADD_LIBRARY(
    safe_thermometer 
    safe_thermometer.cpp
)

ADD_EXECUTABLE(
    Michael.Mayer.sensor-tests
    sensor-tests.cpp
)
TARGET_LINK_LIBRARIES(
    Michael.Mayer.sensor-tests
    sensors
    safe_thermometer
)
