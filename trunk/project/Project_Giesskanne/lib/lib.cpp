/*
 * Common functions used by both the client and the server.
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include "lib.h"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

/**
 * Create a new socket instance.
 * @return fd of the socket instance
 *  */
int create_socket()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
      print_errno("failed to create socket");
    return socket_fd;
}

/**
 * Bind a socket to a port.
 *
 * @param socket_fd fd of the socket
 * @param port port the socket is bound to
 *  */
int bind_socket(int socket_fd, int port)
{
  struct sockaddr_in server;
  memset(&server, sizeof(server), 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(socket_fd, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
  {
    close(socket_fd);
    print_errno("failed to bind socket");
    return SOCKET_ERROR;
  }
  return 1;
}

/**
 * Listen on a socket.
 *
 * @param socket_fd fd of the socket which will start to listen on the bound port
 * */
int listen_on_socket(int socket_fd)
{
  if ((listen(socket_fd, MAX_CLIENTS)) == SOCKET_ERROR)
  {
    print_errno("failed to listen");
    close(socket_fd);
    return SOCKET_ERROR;
  }
  return 1;
}

/**
 * Write error and exit.
 *
 * @param message text that is written as an error
 * */
void print_errno(const char* message)
{
  perror(message);
}

/**
 * get own IP address.
 *
 * @param acIp
 * */
int getOwnIp (char* acIp)
{
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_in *sa;
  char *addr;
  getifaddrs (&ifap);
  for (ifa = ifap; ifa; ifa = ifa->ifa_next)
  {
    if (ifa->ifa_addr->sa_family==AF_INET)
    {
	  sa = (struct sockaddr_in *) ifa->ifa_addr;
	  addr = inet_ntoa(sa->sin_addr);
      if(strcmp(ifa->ifa_name,"eth0") == 0)
      {
	    struct sockaddr_in* addr = (sockaddr_in*) ifa->ifa_addr;
		inet_ntop(AF_INET, &(addr->sin_addr), acIp, INET_ADDRSTRLEN);
		freeifaddrs(ifap);
		return 1;
	  }
	}
  }
	freeifaddrs(ifap);
	return -1;
}
