# Because we compile the entire processes project we must include sensors directory like that 
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
  Kranabetter.Lukas.safe_thermometer
	safe_thermometer.cpp
	safe_thermometer-test.cpp
)

TARGET_LINK_LIBRARIES(
  Kranabetter.Lukas.safe_thermometer
  sensors
)