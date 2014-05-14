INCLUDE_DIRECTORIES(
    ../sensors
)

ADD_EXECUTABLE(
    Haberl.Hans-Georg.safe_thermometer
    save_thermometer.cc
    test_save_thermometer.cc
)
TARGET_LINK_LIBRARIES(
    Haberl.Hans-Georg.safe_thermometer
    sensors
)
