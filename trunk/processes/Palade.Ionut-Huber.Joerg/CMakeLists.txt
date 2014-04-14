CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0 FATAL_ERROR)

INCLUDE_DIRECTORIES(
	../sensors
)

ADD_EXECUTABLE(
	Palade.Ionut-Huber.Joerg.safe_thermometer
	safe_thermometer.cpp
	safe_test.cpp
)

TARGET_LINK_LIBRARIES(
	Palade.Ionut-Huber.Joerg.safe_thermometer
	sensors
)
