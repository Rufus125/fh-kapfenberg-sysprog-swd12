INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    dulzky.florian
    safeThermometer.cpp
    safeThermometerTest.cpp
)
TARGET_LINK_LIBRARIES(
    dulzky.florian
    sensors
)