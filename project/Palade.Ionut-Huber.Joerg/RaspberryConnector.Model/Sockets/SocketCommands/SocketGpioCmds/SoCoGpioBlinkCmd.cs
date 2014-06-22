using System;
using Raspberry.IO.GeneralPurpose;

namespace RaspberryConnector.Model.Sockets.SocketCommands.SocketGpioCmds
{
    [Serializable]
    public class SoCoGpioBlinkCmd : SocketGpioCmd
    {
        public ConnectorPin ConnectorPin { get; set; }

        public override void Execute()
        {
            //Connection.Blink(ConnectorPin.ToProcessor());
        }
    }
}
