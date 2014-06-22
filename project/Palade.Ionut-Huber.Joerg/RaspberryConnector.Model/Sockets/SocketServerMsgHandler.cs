using RaspberryConnector.Model.GpioPins;
using RaspberryConnector.Model.NetworkSerializes;
using RaspberryConnector.Model.Sockets.SocketCommands;
using RaspberryConnector.Model.Sockets.SocketCommands.SocketGpioCmds;

namespace RaspberryConnector.Model.Sockets
{
    public class SocketServerMsgHandler : ISocketServerMsgHandler
    {


        private readonly GpioDriverHelper _driverHelper;

        private readonly NetworkSerializer _serializer = new NetworkSerializer();

        public SocketServerMsgHandler(GpioDriverHelper driverHelper)
        {
            _driverHelper = driverHelper;
        }

        public string HandleRequest(string msgFromClient)
        {
            var cmd = _serializer.Deserialize(msgFromClient);

            var socketCommand = cmd as ISocketCommand;
            if (socketCommand != null)
            {
                HandleSocketCommand(socketCommand);
            }
            return "";
        }


        private void HandleSocketCommand(ISocketCommand socketCommand)
        {
            //inject GpioConnection
            var socketGpioCmd = socketCommand as SocketGpioCmd;
            if (socketGpioCmd != null)
            {
                socketGpioCmd.DriverHelper = _driverHelper;
            }

            socketCommand.Execute();
        }
    }
}
