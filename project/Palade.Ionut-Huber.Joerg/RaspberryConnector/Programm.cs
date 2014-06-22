using System;
using System.Threading;
using Raspberry.IO.GeneralPurpose;
using RaspberryConnector.Model.GpioPins;
using RaspberryConnector.Model.Sockets;
using RaspberryConnector.Model.Sockets.SocketUtils;


namespace RaspberryConnector
{
    public class Programm
    {

        static void Main(string[] args)
        {
            Console.WriteLine("Led switch example start");

            try
            {

                var driver = GpioConnectionSettings.DefaultDriver;


                var ip = new IpAddressHelper().GetIpAddress();
                const int port = 11000;

                //run Socket Server in Thread
                var driverHelper = new GpioDriverHelper(driver);
                var handler = new SocketServerMsgHandler(driverHelper);

                ThreadPool.QueueUserWorkItem(delegate
                {
                    var server = new SocketServer(ip, port, handler);
                    server.StartListening();
                });


                while (true)
                {
                    Thread.Sleep(10000);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }

    }
}
