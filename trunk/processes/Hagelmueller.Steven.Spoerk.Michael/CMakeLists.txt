INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    Hagelmueller.Spoerk.sensor-tests
    safe_thermometer.cpp sensor-tests.cpp
)

TARGET_LINK_LIBRARIES(
    Hagelmueller.Spoerk.sensor-tests
    sensors
)
