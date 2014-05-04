INCLUDE_DIRECTORIES(
../sensors
)

ADD_EXECUTABLE(
Robert.Muehlberger.safe_thermometer
safe_thermometer.cpp
safe-tests.cpp
)
TARGET_LINK_LIBRARIES(
Robert.Muehlberger.safe_thermometer
sensors
)