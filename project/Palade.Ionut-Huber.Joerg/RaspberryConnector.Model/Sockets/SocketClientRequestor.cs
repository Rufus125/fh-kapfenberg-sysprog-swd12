using System.Net;
using RaspberryConnector.Model.NetworkSerializes;
using RaspberryConnector.Model.Sockets.SocketCommands.SocketGpioCmds;

namespace RaspberryConnector.Model.Sockets
{
    public class SocketClientRequestor
    {
        private readonly SocketClient _socketClient;
        private readonly NetworkSerializer _serializer = new NetworkSerializer();

        public SocketClientRequestor(IPAddress ip, int port)
        {
            _socketClient = new SocketClient(ip, port);
        }


        public void Send(SoCoGpioToggleCmd cmd)
        {
            //serialze & send
            var xml = _serializer.Serialize(cmd);
            _socketClient.SendMsgToServer(xml);
        }
    }
}
