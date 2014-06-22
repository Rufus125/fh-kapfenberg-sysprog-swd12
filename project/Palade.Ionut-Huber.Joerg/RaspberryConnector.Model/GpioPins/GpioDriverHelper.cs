using System;
using System.Collections.Generic;
using Raspberry.IO.GeneralPurpose;

namespace RaspberryConnector.Model.GpioPins
{
    public class GpioDriverHelper
    {
        private readonly HashSet<ConnectorPin> _allocatedPins = new HashSet<ConnectorPin>();

        public readonly IGpioConnectionDriver Driver;

        public GpioDriverHelper(IGpioConnectionDriver driver)
        {
            Driver = driver;
        }


        public void AllocatePin(ConnectorPin connectorPin)
        {
            if (!_allocatedPins.Contains(connectorPin))
            {
                Driver.Allocate(connectorPin.ToProcessor(), PinDirection.Output);
                _allocatedPins.Add(connectorPin);
                var msg = string.Format("{0} pin allocated", connectorPin);
                Console.WriteLine(msg);
            }
        }
    }
}
