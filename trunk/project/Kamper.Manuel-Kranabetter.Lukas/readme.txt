SWD12 Ampel project

Manuel Kamper, Lukas Kranabetter

Description:
------------

Exercise project for system programming with c#. Program run on a raspberry pi and simulates a traffic light control.

Detailed description at http://www.manuelkamper.com/ampel.php

Containing projects:

- RaspiAmpel (RaspiAmpel/RaspiAmpel)
	The main traffic light control program.
	
- RaspiGpioTest (RaspiGpioTest/RaspiGpioTest)
	Test program for raspberry io ports.

Build and deploy process:
-------------------------

To be system and IDE independent we build and deploy the project with gradle. This allows us to build it even on a
continuous integration system like jenkins. The gradle msbuild plugin read *.csproj file from the project to compile
c# source dependent on the settings made in the IDE (Visual Studio, Monodevelop). 

When build process should be launched from CI system be aware to change the login data request from console to hardcoded values.   

System requirements:
- Java JRE

Important gradle commands:

gradlew - Gradle wrapper, use gradlew instead of gradle command when gradle is not yet installed
gradle projects - Show all projects
gradle tasks - Show all available tasks
gradle msbuild - Run msbuild task for all projects to compile source files
gradle deploy - Run deploy task for all projects to copy the executable files to the raspberry /tmp/deploy/ directory
gradle :<project name>:<any project task> - Run task of a specific project

Gradle tasks can be executed togehter - gradle msbuild deploy

Build properties:

Can be added in the gradle.properties file and over command line -Pname=value
Scp username and password will be requested by console when not set as a property

Version history:
----------------

v1.0:
   