INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
    schlagholz.georg_platzer.franz.safe_thermometer
    safe_test.cpp
)
TARGET_LINK_LIBRARIES(
    sensors
)