INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    Reitner.Holger.safeThermometer
    safeThermometer.cpp
    safeThermometer_Test.cpp
)
TARGET_LINK_LIBRARIES(
    Reitner.Holger.safeThermometer
    sensors
)
