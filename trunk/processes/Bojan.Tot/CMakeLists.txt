# Because we compile the entire processes project we must include sensors directory like that 
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
  Bojan.Tot.safe_thermometer
	safe_thermometer.cc
	safe_thermometer_test.cc
)

TARGET_LINK_LIBRARIES(
  Bojan.Tot.safe_thermometer
  sensors
)
