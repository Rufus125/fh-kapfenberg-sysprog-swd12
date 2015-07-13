# Introduction #
Projekt von Florian Dulzky

Am RaspberryPi wird ein Gewichtssensor (PPSEN-10245) über einen ADC (Analog to digital converter) angeschlossen.
Des weiteren läuft am RaspberryPi ein Timer der einen Alarm auslöst (Wecker), der Alarm wird erst deaktiviert wenn der Gewichtssensor mindestens 30kg weniger misst.
Also ein Wecker der erst aufhört zu läuten wenn man aufsteht :)

# Details #

Komponenten:
> - RaspberryPi<br>
<blockquote>- LCD-Display<br>
- ADC (Analog to Digital converter): ADC PI v2.2<br>
- Gewichtssensor: PPSEN- 10245<br>