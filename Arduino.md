# Introduction #

Mitglieder:
- Almer Patrick
- Kotremba Achim
- Windhaber Thomas

# Details #


**Hardware:**

- Rasberry Pi (Client)

- LCD Display

- Arduino Uno (Mikrocontroller)

- Steckboard mit Lichtern und Schaltern


**Aufbau:**

Der Rasberry Pi wird über GPIO mit dem LCD Display verbunden.
Weiters wird der Arduino Uno Mikrokontroller über eine USB Schnittstelle mit dem Rasberry Pi verbunden.

Der Arduino Uno wird mit dem Steckboard über die I/O-Schnittstellen verbunden.

**Programme:**

Arduino Uno:
Auf dem Arduino Uno läuft ein C Programm, welches sich um die Schaltung der Lichter kümmert die über die Schalter am Steckboard geschalten werden sollen.
Beim Schalten eines Lichtes wird der Zustand des Lichtes/Schalters über eine USB-Schnittstelle an den Rasberry Pi übertragen.

Rasberry Pi:
Auf dem Rasberry Pi läuft ein C++ Programm welches die USB-Schnittstelle auf Eingaben vom Rasberry Pi lauscht.
Weiters kümmert das Programm sich um die Verbindung zum LCD-Display das an der GPIO-Schnittstelle hängt und zeigt dort die Informationen über die geschalteten Lichter an.