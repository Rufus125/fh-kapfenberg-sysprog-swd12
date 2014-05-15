# Include sensor directory
INCLUDE_DIRECTORIES(
  ../sensors
)

# safe thermometer
ADD_EXECUTABLE(
  Temmel.Philipp.safe_thermometer
  safe_thermometer.cpp
  safe-thermometer_tests.cpp
)
TARGET_LINK_LIBRARIES(
  Temmel.Philipp.safe_thermometer
  sensors
)