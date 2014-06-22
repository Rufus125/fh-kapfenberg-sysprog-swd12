using System;
using Raspberry.IO.GeneralPurpose;

namespace RaspberryConnector.Model.Sockets.SocketCommands.SocketGpioCmds
{
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
}
