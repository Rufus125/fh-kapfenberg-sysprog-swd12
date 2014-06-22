using System;
using System.Net;
using log4net;
using Raspberry.IO.GeneralPurpose;
using RaspberryConnector.Model.NetworkSerializes;
using RaspberryConnector.Model.Sockets;
using RaspberryConnector.Model.Sockets.SocketCommands.SocketGpioCmds;
using RaspberryControler.Properties;

namespace RaspberryControler.Views.MainView.RelayCommands
{
    class SendCmd : AbstractMainCmd
    {
        private readonly NetworkSerializer _serializer = new NetworkSerializer();

        public SendCmd(MainViewModel viewModel, ILog logger)
            : base(viewModel, logger)
        {
        }

        public override bool CanExecute(object parameter)
        {
            if (ViewModel.IpAddressString == null)
                return false;

            try
            {
                IPAddress.Parse(ViewModel.IpAddressString);
            }
            catch (FormatException)
            {
                return false;
            }
            return true;
        }

        public override void SecureExecute(object parameter)
        {
            Settings.Default.IpAddressStore = ViewModel.IpAddressString;
            Settings.Default.PortStore = ViewModel.Port;
            Settings.Default.Save();

            var ip = IPAddress.Parse(ViewModel.IpAddressString);

            //create cmd
            var cmd = new SoCoGpioToggleCmd
            {
                ConnectorPin = ViewModel.SelPinConfiguration.Pin.ToConnector()
            };

            var reqestor = new SocketClientRequestor(ip, ViewModel.Port);
            reqestor.Send(cmd);
        }
    }
}
