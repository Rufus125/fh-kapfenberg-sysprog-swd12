INCLUDE_DIRECTORIES(
	../sensors
)

ADD_EXECUTABLE(
	Palade.Ionut-Huber.Joerg.ex
	safe_thermometer.cpp
	safe_test.cpp
)

TARGET_LINK_LIBRARIES(
	Palade.Ionut-Huber.Joerg.ex
	sendors
)
