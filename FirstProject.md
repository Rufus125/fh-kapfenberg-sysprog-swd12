# Schon wieder ein Kopierprogramm #

## Aufgabenstellung ##

Schreiben Sie ein Programm, das ein File auf ein anderes kopiert, und
dazu die Systemcalls open/read/write/close benützt.

Das Programm erhält zwei Commandline-Argumente (sehen Sie dazu das
grössere CMake-Demoprojekt im SVN), SOURCE und DESTINATION. Wenn
SOURCE existiert und DESTINATION nicht existiert, kopiert es den
Inhalt von SOURCE auf DESTINATION (das zuvor angelegt wird).

```
$ ./yacp SOURCE DESTINATION
```

Die "Challenge" dabei ist, open() zu verstehen, und da vor allem das
`flags` Argument. Bitte lesen Sie die Manpage genau, vor allem die
Bedeutung von `O_CREAT`. Machen Sie die Fehlerbehandlung ungefähr
so, wie im Kurs erläutert wurde.

Bitte halten Sie sich an die Unix-Gebräuche:

  * Geben Sie keine Meldungen auf `stdout` aus, die dort nicht hingehören. Dort gehören nur Sachen hin, die mittels einer Pipe ins nächste Programm übergeben werden sollen --- das sind **keine** Fehler-, Status- und Debugmessages.
  * Geben Sie dem Benutzer im Fehlerfall _sämtliche_ Information, die Sie haben. Insbesondere achten Sie bitte darauf, ihm die textuelle Information zur `errno` Variable zu präsentieren.

Bitte legen Sie sich eigene Arbeitsbereiche in
https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/file-copy
an, Gruppen zu maximal zwei Mitgliedern sind erlaubt. Der
Arbeitsbereich sollte so heissen, wie der Teilnehmer oder die
Gruppe, zum Beispiel `Mitteregger.Christoph`, oder `Mitteregger.Christoph-Mayer.Michael`.
Jeder Arbeitsbereich enthält ein eigenes CMake-Projekt; als
Beispiel sollte
https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/cmake-demo/hello-project-monolithic
genügen.

## Testfälle ##

  * Bricht ab, wenn `DESTINATION` bereits existiert. `errno` ist in diesem Fall `EEXIST` (mit der zugehörigen Message "File exists").
  * Kopiert auch große Files als ganzes
  * `SOURCE` und `DESTINATION` sind danach identisch
  * Keine Ausgabe auf `stdout`
  * Die Permissions von `DESTINATION` sind nach erfolgreicher Operation die gleichen, die auch das Command `touch DESTINATION` vergeben würde.
  * `valgrind ./yacp SOURCE DESTINATION` beschwert sich nicht.

## Abgabe ##

Als Abgabeordner fungiert der obige Arbeitsbereich, ein
Directory.

  * Stichtag, sagen wir 3.April, bei unserer nächsten Veranstaltung.
  * Nachfrist wegen unzureichend präziser Aufgabenstellung: 10.4.2014