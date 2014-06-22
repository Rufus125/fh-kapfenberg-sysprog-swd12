using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace RaspberryConnector.Model.Sockets
{
    public class SocketServer
    {
        private readonly ISocketServerMsgHandler _msgHandler;
        private readonly IPAddress _ipAddress;
        private readonly int _port;

        public SocketServer(IPAddress ipAddress, int port, ISocketServerMsgHandler msgHandler)
        {
            _ipAddress = ipAddress;
            _port = port;
            _msgHandler = msgHandler;
        }

        public void StartListening()
        {
            // Data buffer for incoming data.

            // Establish the local endpoint for the socket.
            var localEndPoint = new IPEndPoint(_ipAddress, _port);

            // Create a TCP/IP socket.
            var listener = new Socket(AddressFamily.InterNetwork,
                SocketType.Stream, ProtocolType.Tcp);

            // Bind the socket to the local endpoint and 
            // listen for incoming connections.

            listener.Bind(localEndPoint);
            listener.Listen(10);

            // Start listening for connections.
            while (true)
            {
                Console.WriteLine("Waiting for a connection...");
                // Program is suspended while waiting for an incoming connection.
                var handler = listener.Accept();
                string data = null;

                // An incoming connection needs to be processed.
                const string eof = "<EOF>";
                while (true)
                {
                    var bytes = new byte[1024];
                    var bytesRec = handler.Receive(bytes);
                    data += Encoding.ASCII.GetString(bytes, 0, bytesRec);
                    if (data.IndexOf(eof, StringComparison.Ordinal) > -1)
                    {
                        break;
                    }
                }

                // Show the data on the console.
                //     Console.WriteLine("Text received : {0}", data);
                var msgForClient = _msgHandler.HandleRequest(data.Replace(eof,""));


                // Echo the data back to the client.
                var msg = Encoding.ASCII.GetBytes(msgForClient);

                handler.Send(msg);
                handler.Shutdown(SocketShutdown.Both);
                handler.Close();
            }
        }


    }
}
