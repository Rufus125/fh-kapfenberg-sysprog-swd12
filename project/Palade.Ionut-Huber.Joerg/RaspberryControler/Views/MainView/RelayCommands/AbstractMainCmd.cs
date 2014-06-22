using log4net;
using Wpf.Utils.Commands;

namespace RaspberryControler.Views.MainView.RelayCommands
{
    abstract class AbstractMainCmd : AbstractRelayCommand
    {
        protected readonly MainViewModel ViewModel;

        protected AbstractMainCmd( MainViewModel viewModel,ILog logger) : base(logger)
        {
            ViewModel = viewModel;
        }
    }
}
