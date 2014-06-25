#!/usr/bin/python3
# coding=UTF-8
# Author: Georg Schlagholz
# Teammembers:Georg Schlagholz, Franz Platzer, Michael Mayer 
import ServerInfo
import http.server
import ssl
import socketserver
import socket
#This class will handle any incoming request from
#the browser


# openssl req -new -x509 -newkey rsa:2048 -out cert.csr -nodes
# cat privkey.pem cert.csr >> localhost.pem

class MyHandler(http.server.SimpleHTTPRequestHandler):
    #Handler for the GET requests
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain; charset=utf-8') #UTF-8 for degree sign
        self.end_headers()
        # Send the response
        hostname, temp = ServerInfo.ServerInfo().getInfos()
        response = "Hostname: " + hostname + "\tTemperature: " + str(temp) + " °C\n"
        self.wfile.write(bytes(response, 'UTF-8'))
        return


try:
    ipaddr = [(s.connect(('8.8.8.8', 80)), s.getsockname()[0], s.close()) for s in
              [socket.socket(socket.AF_INET, socket.SOCK_DGRAM)]][0][1] #get ipaddr
    port = 4443
    server_address = (ipaddr, port)
    httpd = http.server.HTTPServer(server_address, MyHandler)
    httpd.socket = ssl.wrap_socket(httpd.socket,
                                   server_side=True,
                                   certfile='localhost.pem',
                                   ssl_version=ssl.PROTOCOL_TLSv1)
    print("Starting server: https://"+ipaddr+":"+str(port))
    httpd.serve_forever()

except KeyboardInterrupt:
    httpd.socket.close()
    print(' received, shutting down the web server')