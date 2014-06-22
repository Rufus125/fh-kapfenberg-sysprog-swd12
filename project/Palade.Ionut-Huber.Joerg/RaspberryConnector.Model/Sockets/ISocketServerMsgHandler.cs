namespace RaspberryConnector.Model.Sockets
{
    public interface ISocketServerMsgHandler
    {
        string HandleRequest(string msgFromClient);
    }
}
