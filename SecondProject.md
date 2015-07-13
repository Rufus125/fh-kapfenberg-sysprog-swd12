# Spielen mit den Prozessen: Temperatursensoren #

Man stelle sich Hardware-Temperatursensoren vor, die wir auslesen
wollen. Beim nächsten Übungsbeispiel wollen wir ein wenig in die
Breite gehen und unter anderem I2C-Temperatursensoren mit einem
Raspberry-Pi auslesen. Einstweilen muss folgendes Gedankenbeispiel
genügen ...

![http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/processes/sensors/sensors.png](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/processes/sensors/sensors.png)

Zwei von diesen Sensor-Implementationen haben ein Problem:

  * `HangThermometer` lässt sich mitunter zu lange Zeit, sodass eine verwendende Datenloggerapplikation, die 100e Sensoren betreut, Probleme hätte.
  * `CrashThermometer` stürzt gar ab.

Schreiben Sie eine Thermometer-Klasse SafeThermometer,

![http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/processes/sensors/safe-thermometer.png](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/processes/sensors/safe-thermometer.png)

`SafeThermometer` _besitzt_ ein (instabiles) Thermometer, das es
benutzt, um die Temperatur zu messen. Um sich und die Umwelt von der
Instabilität zu schützen, macht seine Implementation von
`get_temperature()` folgendes:

  * Jeden Aufruf von `get_temperature()` des instabilen Thermometers führt es in einem eigenen Adressraum durch (`fork()`).
  * Um ein Timeout zu implementieren, wird im Child-Prozess `alarm()` benutzt. Bitte lesen Sie `man 2 alarm`, um die Semantik zu erfahren, bzw. lesen Sie dazu [das Testprogramm](http://code.google.com/p/fh-kapfenberg-sysprog-swd12/source/browse/trunk/processes/Joerg.Faschingbauer/alarm-test.cpp)
  * `SafeThermometer` verwendet `waitpid()`, um den Exitstatus des Child zu inspizieren. Auf einen fehlerhaften Exitcode reagiert der Parent mit einer entsprechenden Exception (siehe dazu die [Definition der Basisklasse](http://code.google.com/p/fh-kapfenberg-sysprog-swd12/source/browse/trunk/processes/sensors/thermometer.h)).
  * Bei erfolgreichem Lesen der Temperatur wird eine vom Parent ans Child vererbte Pipe verwendet, um die Temperatur an den eigentlichen Aufrufer zu kommunizieren. Siehe dazu [das entsprechende Testprogramm](http://code.google.com/p/fh-kapfenberg-sysprog-swd12/source/browse/trunk/processes/Joerg.Faschingbauer/pipe-test.cpp).

![http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/fork-pipe.jpg](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/fork-pipe.jpg)

# Organisatorisches #

## Arbeitsbereiche ##

Das Projekt-Rootdirectory ist
[hier](http://code.google.com/p/fh-kapfenberg-sysprog-swd12/source/browse/trunk/processes/).
Darunter liegen die Arbeitsbereiche; jeder Arbeitsbereich wird
mit dem Gesamtprojekt **mitgebaut** --- was unter Umständen zu
Anfeindungen unter den Mitgliedern führen wird, wenn nicht jeder
einzelne darauf achtet, funktionierenden Code einzuchecken.

Die Thermometer-Implementationen aus dem UML-Diagramm liegen in
[einem eigenen Subdirectory](http://code.google.com/p/fh-kapfenberg-sysprog-swd12/source/browse/trunk/processes/sensors/), das von allen Arbeitsbereihen als Library
gelinkt wird. Hier sollte keine Änderung nötig sein (ausser Bugfixes vielleicht), alles sollte sich in den Arbeitsbereichen abspielen.

## Kriterien ##

  * In jedem Arbeitsbereich befinden sich
    * Ein .h File und ein .cpp (.cc, oder wie man auch immer C++ Files benennt), die das Thermometer beinhalten.
    * Ein Testprogramm, das das Thermometer instanziiert, von ihm die Temperatur erfragt, und auf `stdout` ausgibt.
  * Keine Ausgaben auf `stdout`, ausser der Temperatur

## Abgabe ##

  * Als Abgabeordner fungiert der obige Arbeitsbereich, ein Directory.
  * Abgabetermin ist 8.5.2014. Zu diesem Zeitpunkt sollten alle Fragen geklärt und alle Files eingecheckt sein.
  * Weiter Verlängerung wegen Stress: 15.5.2014