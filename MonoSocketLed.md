# Introduction #

Ansteuerung einer LED am Raspberry Pi mittels Socket-Verbindung.
Als Programmiersprache wird C# in Verbindung mit MONO verwendet.


# Details #

Teammitglieder: Palade Ionut, Huber Jörg

Ziel ist es, einen Gpio-Pin über eine Socket-Verbindung zu steuern.
Als Client-Anwendung wird eine WPF-Applikation verwendet. Die Programmiersprache C# wird sowohl am Client (Windows) als auch am Server (Linux) verwendet. Die Ansteuerung der Pins am Raspberry erfolgt mit Hilfe der Library raspberry-sharp-io.


CLIENT

Die Client-Applikation dient zur Eingabe der Netzwerkdaten und zur Selektion des gewünschten Pins.
![https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/RaspberryControler.png](https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/RaspberryControler.png)

Um eine typensichere Übertragung über das Netzwerk zu erreichen, wird ein Command-Objekt eingesetzt. Dieses Objekt wird auf der Clientseite serialisiert und anschließend über die Socket Verbindung übertragen.

  * der Client übergibt dem SocketClientRequestor ein Objekt, das das Interface ISocketCommand implementiert
  * der SocketClientRequestor serialisert das Objekt und übergibt es dem SocketClient
  * SocketClient baut eine Verbindung zum SocketServer (Raspberry) auf und übermittelt das serialisierte Objekt

![https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/ClientClassDiagramm.png](https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/ClientClassDiagramm.png)


SERVER

Auf dem Raspberry läuft über MONO das gleiche C#-Model, daher sind die Interfaces und Klassen des Clients bekannt. Sobald eine Socket-Verbindung geöffnet wurde, werden die übertragenen Daten verarbeitet (in diesem Fall wird Pin4 gesetzt).

![https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/RaspberryConnector.png](https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/RaspberryConnector.png)

  * der SocketServer wartet auf eingehende Verbindungen
  * nachdem er eine Nachricht empfangen hat, übergibt er diese dem SocketServerMsgHandler
  * der SocketServerMsgHandler deserialsiert die Nachricht und erstellt ein Objekt, welches das ISocketCommand Interface implementiert
  * handelt es sich um eine SocketGpioCmd-Kommando, injeziert der SocketServerMsgHandler den GpioDriverHelper
  * anschließend ruft der SocketServerMsgHandler die Execute-Methode am ISocketCommand auf und der Pin ändert seinen Status


![https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/ServerClassDiagramm.png](https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Palade.Ionut-Huber.Joerg/Images/ServerClassDiagramm.png)


```

    [Serializable]
    public class SoCoGpioToggleCmd : SocketGpioCmd
    {
        public ConnectorPin ConnectorPin { get; set; }

        public override void Execute()
        {
            //allocatedthe pin if the pin is not allocated until now
            DriverHelper.AllocatePin(ConnectorPin);

            //read the current state of the pin
            var state = DriverHelper.Driver.Read(ConnectorPin.ToProcessor());
            Console.WriteLine("current state:" + state);

            //invert the state and write it to the pin
            DriverHelper.Driver.Write(ConnectorPin.ToProcessor(), !state);
            Console.WriteLine("new state:" + DriverHelper.Driver.Read(ConnectorPin.ToProcessor()));
        }
    }

```

Der GpioDriverHelper existiert nur am Raspberry und wird deshalb nicht übertragen, sondern vom SocketServerMsgHandler am Client gesetzt.

```
    [Serializable]
    public abstract class SocketGpioCmd : ISocketCommand
    {
        [NonSerialized]
        public GpioDriverHelper DriverHelper;

        public abstract void Execute();

    }
```