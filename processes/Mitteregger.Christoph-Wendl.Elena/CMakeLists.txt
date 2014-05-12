INCLUDE_DIRECTORIES(
    ../sensors
)

ADD_EXECUTABLE(
    Mitteregger-Wendl.safe_thermometer
    safe_thermometer.cpp
    thermometer_test.cpp
)
TARGET_LINK_LIBRARIES(
    Mitteregger-Wendl.safe_thermometer
    sensors
)
