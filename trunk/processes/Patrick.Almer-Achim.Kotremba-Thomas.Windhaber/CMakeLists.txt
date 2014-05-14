INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    Patrick.Almer-Achim.Kotremba-Thomas.Windhaber.safe_thermometer
    safe_thermometer.cpp
    safe_thermometer_test.cpp
)
TARGET_LINK_LIBRARIES(
    Patrick.Almer-Achim.Kotremba-Thomas.Windhaber.safe_thermometer
    sensors
)
