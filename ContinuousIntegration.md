## Projektmitglieder ##

  * MARCHER, Sandra
  * REITNER, Holger
  * SIHARATH, Herbert
  * TOT, Bojan

## SVN ##

https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Marcher.Reitner.Siharath.Tot

# Idee #

Jenkins ruft nach dem Build ein Programm auf, das ein Alarm-Licht ein-
bzw. ausschaltet, je nachdem, ob der Build gut oder schlecht war.

```
$ build-alarm 192.168.2.34 1234 on # alarm ein
$ build-alarm 192.168.2.34 1234 off # alarm aus
```

Am Buildserver gibts meistens keine Möglichkeit, IO Pins zu schalten
(wie generell PCs nicht für sowas gedacht sind), deswegen wird ein
Raspberry als Alarmlichtserver abgestellt und ist z.B. unter
192.168.2.34 erreichbar.

![http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/jenkins-alarm.jpg](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/jenkins-alarm.jpg)

![http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/GPIO.png](http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/docs/GPIO.png)

Aufgaben:

  * Hardwarebasteln am Raspi (siehe [hier, "Schaltstufe für kleine Lasten"](http://www.mikrocontroller.net/articles/Relais_mit_Logik_ansteuern#Schaltstufe_f.C3.BCr_kleine_Lasten). BC337 (links im Bild) ist getestet, erhältlich z.B. bei Conrad)
  * Ansteuern des IO am Server
  * Netzwerkprogrammierung
    * Server
    * Client
  * Jenkins-Administration

# Installation/Inbetriebnahme Jenkins (Fedora 19 VM) #

Jenkins installieren
  * `sudo wget -O /etc/yum.repos.d/jenkins.repo http://pkg.jenkins-ci.org/redhat/jenkins.repo`
  * `sudo rpm --import http://pkg.jenkins-ci.org/redhat/jenkins-ci.org.key`
  * `sudo yum install jenkins`
Jenkins starten
  * `sudo service jenkins start/stop/restart`
  * `sudo chkconfig jenkins on`
Jenkins Web-Oberfläche ist nun verfügbar
  * http://localhost:8080


# Zusätzliche Informationen / Links #

  * Jenkins Website: http://jenkins-ci.org/
  * Jenkins Wiki: http://de.wikipedia.org/wiki/Jenkins_%28Software%29