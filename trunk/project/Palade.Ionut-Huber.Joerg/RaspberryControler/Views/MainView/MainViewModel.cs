using System.Collections.Generic;
using System.Windows.Input;
using log4net;
using Raspberry.IO.GeneralPurpose;
using RaspberryConnector.Model.GpioPins;
using RaspberryControler.Properties;
using RaspberryControler.Views.MainView.RelayCommands;
using Wpf.Utils.Commands;
using Wpf.Utils.KindOfMagic;
using Wpf.Utils.ViewModels;

namespace RaspberryControler.Views.MainView
{
    public class MainViewModel : NotifyViewModel
    {
        protected static readonly ILog Log = LogManager.GetLogger(typeof(MainViewModel));

        public MainViewModel()
        {
            IpAddressString = Settings.Default.IpAddressStore;
            Port = Settings.Default.PortStore;
            PinConfigurations = GpioPinConf.PinConfigurations();
        }

        AbstractRelayCommand _sendCommand;
        public ICommand SendCommand { get { return _sendCommand ?? (_sendCommand = new SendCmd(this, Log)); } }

        [Magic]
        public string IpAddressString { get; set; }

        [Magic]
        public List<PinConfiguration> PinConfigurations { get; set; }

        [Magic]
        public PinConfiguration SelPinConfiguration { get; set; }

        public int Port { get; set; }

    }
}
