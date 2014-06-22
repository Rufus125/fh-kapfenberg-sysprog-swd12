using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace RaspberryConnector.Model.Sockets
{
    class SocketClient
    {

        private readonly IPAddress _ipAddress;
        private readonly int _port;

        public SocketClient(IPAddress ipAddress, int port)
        {
            _ipAddress = ipAddress;
            _port = port;
        }


        public string SendMsgToServer(string msgForServer)
        {
            // Data buffer for incoming data.
            var bytes = new byte[1024];

            string msgFromServer = null;


            // Establish the remote endpoint for the socket.
            var remoteEp = new IPEndPoint(_ipAddress, _port);

            // Create a TCP/IP  socket.
            var sender = new Socket(AddressFamily.InterNetwork,
                SocketType.Stream, ProtocolType.Tcp);

            sender.Connect(remoteEp);

            Console.WriteLine("Socket connected to {0}",
                sender.RemoteEndPoint);

            // Encode the data string into a byte array.
            var msg = Encoding.UTF8.GetBytes(msgForServer + "<EOF>");

            // Send the data through the socket.
            //   var bytesSent = sender.Send(msg);
            sender.Send(msg);

            // Receive the response from the remote device.
            var bytesRec = sender.Receive(bytes);
            msgFromServer = Encoding.ASCII.GetString(bytes, 0, bytesRec);


            // Release the socket.
            sender.Shutdown(SocketShutdown.Both);
            sender.Close();


            return msgFromServer;
        }
    }

}
