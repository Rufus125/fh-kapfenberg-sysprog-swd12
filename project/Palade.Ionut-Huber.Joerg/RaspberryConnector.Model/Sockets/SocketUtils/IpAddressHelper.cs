using System;
using System.Net;

namespace RaspberryConnector.Model.Sockets.SocketUtils
{
    public class IpAddressHelper
    {
        public IPAddress GetIpAddress()
        {
            var ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ipAddress in ipHostInfo.AddressList)
            {
                Console.WriteLine(ipAddress);
                if (ipAddress.ToString().Substring(0, 2) == "10" || ipAddress.ToString().Substring(0, 2) == "19")
                {
                    return ipAddress;
                }
            }

            throw new Exception();
        }
    }
}
