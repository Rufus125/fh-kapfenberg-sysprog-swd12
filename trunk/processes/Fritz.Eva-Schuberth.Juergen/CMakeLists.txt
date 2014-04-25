INCLUDE_DIRECTORIES(
    ../sensors
)

ADD_EXECUTABLE(
    Fritz.Eva-Schuberth.Juergen.safe_thermometer
    safe_thermometer.cpp
    safe-tests.cpp
)
TARGET_LINK_LIBRARIES(
    Fritz.Eva-Schuberth.Juergen.safe_thermometer
    sensors
)
