# Temperatursensor, Netzwerkübertragung, Anzeige über LED #

Das Projekt ist etwas umfangreicher, weswegen wir es in mehrere
Subprojekte aufspalten.

![http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/TempSensorNetworkLED.png](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/TempSensorNetworkLED.png)

**Implementation ohne Netzwerk**. Eine Endlosschleife macht ...
  * Auslesen der Temperatur (Floatingpoint): "Thermometer, gib mir die Temperatur!"
  * Ausgabe auf eine Anzeigeeinheit: "Anzeige, visuaisiere mir diese Zahl!"
  * N Sekunden schlafen

**Implementation mit Netzwerk**. Das Netzwerkteam stellt einen
_Temperaturserver_ zu Verfügung. Das ist ein Programm, das ein Socket
bedient und auf diesem auf die Aufforderung "Thermometer, gib mir die
Temperatur!" wartet. Um die Antwort geben zu können, hat dieser
Temperaturserver ein Thermometer, das ihm die Frage beantworten kann,
formuliert dessen Antwort als Netzwerkpaket, und schickt sie raus.

Der Client --- das Anzeigeprogramm --- merkt nichts davon. Dort sitzt
die unveränderte Endlosschleife, die, anstatt direkt mit einem
Thermometer zu reden, eben mit einem Objekt redet, das aussieht wie
ein Thermometer, aber keines ist.

**Testen, Simulieren von Komponenten**. Um uns nicht festlegen zu müssen
auf einerseits den Sensor (es gibt mehrere Typen von Sensoren am Markt
als den LM73) und andererseits die Anzeige (ein LED-Bar ist nur eine
von vielen Möglichkeiten, eine Floatingpoint-Zahl zu repräsentieren),
werden wir interfaces definieren.

| **Thermometer-Hierarchie** |
|:---------------------------|
| ![http://fh-kapfenberg-sysprog-itm12.googlecode.com/svn/trunk/docs/ThermometerHierarchy.png](http://fh-kapfenberg-sysprog-itm12.googlecode.com/svn/trunk/docs/ThermometerHierarchy.png) |
| **Visualisierer-Hierarchie** |
| ![http://fh-kapfenberg-sysprog-itm12.googlecode.com/svn/trunk/docs/VisualizerHierarchy.png](http://fh-kapfenberg-sysprog-itm12.googlecode.com/svn/trunk/docs/VisualizerHierarchy.png) |

## Temperatursensor (TMP36) ##

  * Projektmitglieder:
  * Implementationsdetails
    * [TMP36 Datenblatt](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/TemperatursensorTMP36.pdf)
    * [MCP3008 Datenblatt](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/ADConverterMCP3008.pdf)
    * **TODO**: SPI Erklärung ("Es ist alles ganz einfach!")
      * `spi-dev`: [Kernel Documentation](https://www.kernel.org/doc/Documentation/spi/spi-summary), [SPI driver](https://www.kernel.org/doc/Documentation/spi/spidev)
      * **TODO**: Hardwareübergabe (Raspberry, LM73, Netzteil)

## Visualisierung mittels LED-Bar ##

  * Projektmitglieder:

  * Hardware: N mal LED+Widerstand auf einem Steckbrett, geeignet verdrahtet mit dem [26-poligen Raspberry P1-Header](http://fh-kapfenberg-sysprog-itm12.googlecode.com/svn/trunk/docs/raspi-v2-p1-pinout.png)
  * Schalten der LEDs über Linux GPIO Subsystem via `sysfs` (siehe zum Beispiel [hier](http://hertaville.com/2012/11/18/introduction-to-accessing-the-raspberry-pis-gpio-in-c/)). Falls angebracht, kann man das selbe durch die nette [WiringPi Library](http://wiringpi.com/) erreichen.
  * Implementation des `Visualizer` Interface, um die anzuzeigende Zahl auf die Anzahl der zu schaltenden LEDs zu übersetzen