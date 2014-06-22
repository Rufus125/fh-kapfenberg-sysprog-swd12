using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using RaspberryControler.Views.MainView;

namespace RaspberryControler.Views.LogOnView
{
    /// <summary>
    /// Interaction logic for LogOnWindow.xaml
    /// </summary>
    public partial class LogOnWindow : Window
    {
        public LogOnWindow()
        {
            InitializeComponent();
        }

        private void LogOnWindow_OnLoaded(object sender, RoutedEventArgs e)
        {
            var win = new MainWindow( new MainViewModel());
            Close();
            win.ShowDialog();
        }
    }
}
