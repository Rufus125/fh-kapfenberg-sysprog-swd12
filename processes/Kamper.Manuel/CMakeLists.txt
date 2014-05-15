INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/sensors
)

ADD_EXECUTABLE(
	Kamper.Manuel.safe_thermometer
	safe_thermometer.cc
	safe_thermometer-test.cc
)

TARGET_LINK_LIBRARIES(
	Kamper.Manuel.safe_thermometer
	sensors
)
