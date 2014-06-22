using System;
using Raspberry.IO.GeneralPurpose;
using RaspberryConnector.Model.GpioPins;

namespace RaspberryConnector.Model.Sockets.SocketCommands.SocketGpioCmds
{
    [Serializable]
    public abstract class SocketGpioCmd : ISocketCommand
    {
        [NonSerialized]
        public GpioDriverHelper DriverHelper;

        public abstract void Execute();

    }
}
