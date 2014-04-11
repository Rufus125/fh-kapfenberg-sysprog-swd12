INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    Ascher.Thomas-Lamb.Manuel.safe_thermometer
    safe_thermometer.cpp
    safe-tests.cpp
)
TARGET_LINK_LIBRARIES(
    Ascher.Thomas-Lamb.Manuel.safe_thermometer
    sensors
)
