using System.Collections.Generic;
using Raspberry.IO.GeneralPurpose;

namespace RaspberryConnector.Model.GpioPins
{
    public static class GpioPinConf
    {
        public static List<PinConfiguration> PinConfigurations()
        {
            var ll = new List<PinConfiguration>
            {
                new OutputPinConfiguration(ConnectorPin.P1Pin7.ToProcessor()),
                new OutputPinConfiguration(ConnectorPin.P1Pin11.ToProcessor()),
                           new OutputPinConfiguration(ConnectorPin.P1Pin13.ToProcessor()),
            };


            return ll;
        }
    }
}
