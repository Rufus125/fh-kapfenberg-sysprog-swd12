# Time Server #

## Projektmitglieder ##

  * Thomas Ascher
  * Julia Viehberger
  * Manuel Lamb

Unser Projekt trägt den Namen SimpleTimeServer und umfasst einen
Deamon (STD - SimpleTimeDeamon) und einen Client. Der Dienst liefert
die aktuelle Serverzeit zurück.

Serverdesign: Jeder Request wird in einem eigens dafür geforkten Child
abgehandelt.

STS: Der SimpleTimeServer stellt die Kernlogik des Zeit-Services dar. In diesem Paket ist der meiste Server-/Client-Code implementiert. Das Protokoll kommuniziert über den Port 1337 und funktioniert wie folgt: Nach dem sich der Client verbunden hat, schickt der Server unmittelbar die lokale Serverzeit, ohne dabei Performance an einen langwierigen Handshake zu verlieren.

STL: Dies ist der StandardTimecLient, welcher als parameter den Hostnamen des Server erhält und sich direkt nach dem Start zu diesem verbindet um die Zeit abzufragen. Diese wird anschließend auf der Konsole ausgegeben.

STD: Der StandardTimeDeamon stellt die Server-Instanz des Zeitdiesntes dar. Nach dem Start "forked" sich der Deamon/Service vom Hauptprogramm weg und läuft so als eigener Prozess, sprich als Hintergrundservice, weiter, ohne das dabei die Shell blockiert wird.

SVN-Link: https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Ascher.Thomas-Lamb.Manuel-Viehberger.Julia