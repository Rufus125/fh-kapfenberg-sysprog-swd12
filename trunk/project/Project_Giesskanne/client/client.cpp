#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/prctl.h>
#include <signal.h>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>
#include "../lib/lib.h"

using namespace std;
int socket_in_fd = 0;
int outFd = 0;
//function for STRG + C
void sig_handler(int sig);

int main (int argc, char** argv)
{
  signal(SIGINT, sig_handler);

  /* not enough command line args */
  if (argc < 2)
  {
    print_errno("Please provide a valid server address");
    return EXIT_FAILURE;
  }
  // server ip to connect to
  string sIp = argv[1];

  /* Get own IP address. */
  char ownIp[20] = {};
  if (getOwnIp(ownIp) < 1)
  {
    fprintf(stderr,"Couldn't obtain own ip!\n");
    return EXIT_FAILURE;
  }

  /* Create  outgoing socket instance. */
  outFd = create_socket();
  if (outFd < 1 )
  {
    print_errno("Can't create outgoing socket");
    return EXIT_FAILURE;
  }

  /* Create incoming socket instance. */
  socket_in_fd = create_socket();
  if (socket_in_fd < 1 )
  {
    print_errno("Can't create incoming socket");
    return EXIT_FAILURE;
  }

  /* Get free port  */
  string sPort = "0";

  /* bind incoming socket to free port */
  bind_socket(socket_in_fd, atoi(sPort.c_str()));

  /* get port number with getsockname)( */
  struct sockaddr_in addr = {};
  socklen_t len = sizeof(addr);
  if (getsockname(socket_in_fd,(struct sockaddr*) &addr,&len) < 0 )
  {
    print_errno("getsockname failed");
    close(socket_in_fd);
    return EXIT_FAILURE;
  }

  /* Activate socket for incoming connections. */
  if(listen_on_socket(socket_in_fd) == SOCKET_ERROR)
    return EXIT_FAILURE;

  /* create socketaddr struct and conenct to server */
  uint32_t serverIP = htonl(inet_addr(sIp.c_str()));
  uint32_t serverPort = htonl((uint32_t) SERVER_PORT);

  /* Connect to server. */
  struct sockaddr_in server;;
  memset(&server, 0, sizeof(server));/* Clear struct */
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT); /* Internet/IP */
  inet_pton(AF_INET, sIp.c_str(), &(server.sin_addr));

  if (connect(outFd, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR)
  {
    print_errno("Connecting to server failed!");
    close(outFd);
    close(socket_in_fd);
    return EXIT_FAILURE;
  }

  stringstream s;
  s << ntohs(addr.sin_port);
  sPort = s.str();

  /* Create REGISTER telegram. */
  stringstream register_telegram;
  register_telegram << REGISTER_TOKEN << ownIp << ":" << sPort.c_str() << '\0';


  /* Send 'REGISTER' to server.
  * -> hint: send(sockfd, buf, len, flags);*/
  unsigned int length = register_telegram.str().size();

  int send_flags = 0;

  if (send(outFd, &length, sizeof(length),send_flags) < 0 )
  {
    print_errno("Can't register on server");
    close(outFd);
    close(socket_in_fd);
    return EXIT_FAILURE;
  }

  if (send(outFd, register_telegram.str().c_str(), (register_telegram.str().size()),send_flags) < 0 )
  {
    print_errno("Can't register on server");
    close(outFd);
    close(socket_in_fd);
    return EXIT_FAILURE;
  }

  while (42)
  {
    /* waiting for connections */
    /* Accept server connection. */

    int inFd = accept(socket_in_fd, 0, 0);

    if (inFd == SOCKET_ERROR) {
      print_errno("Accepting connection from server failed!\n");
      continue;
    } else
    {
      pid_t pid = fork();
      if (pid > 0) /* PARENT */
      {
        close(inFd);
        /* Read permanently from stdin and send the chat text to the server. */
        while (42)
        {
          //read from StdIn
          string chatInput = "";
          getline(cin, chatInput);

          //String to Terminate Client
          if (chatInput.compare("EXIT") == 0)
          {
            stringstream exitMessage;
            exitMessage << chatInput.c_str() << ownIp << ":" << sPort.c_str() << '\0';
            length = exitMessage.str().size();
            if (send(outFd, &length, sizeof(length), 0) < 0)
            {
              print_errno("Can't send exit-message to server!\n");
            }

            if (send(outFd, exitMessage.str().c_str(), length, 0) < 0)
            {
              print_errno("Can't send exit-message to server!\n");
            }
            close(outFd);
            close(socket_in_fd);
            exit(0);
          }

          // to get the time when message is sent
          time_t Zeitstempel;
          tm *nun;
          Zeitstempel = time(0);
          nun = localtime(&Zeitstempel);

          // chat message: time , ownip, and actual chatmessage
          stringstream chatMessage;
          chatMessage << "[" << nun->tm_hour << ":" << nun->tm_min << "]" << ownIp << ":" << chatInput.c_str() << '\0';

          int send_flags = 0;
          length = chatMessage.str().size();

          if (send(outFd, &length, sizeof(length), send_flags) < 0)
          {
            print_errno("Can't send chat-message to server!\n");
            break;
          }

          if (send(outFd, chatMessage.str().c_str(), length,send_flags) < 0)
          {
            print_errno("Can't send chat-message to server!\n");
            break;
          }
        }
        close(outFd);
        close(socket_in_fd);
        return EXIT_FAILURE;

      }else if (pid == 0)//child
      {
        close(outFd);
        unsigned int messageLength;
        while (42)
        {
          int inFd = accept(socket_in_fd, 0, 0);
          if (inFd == SOCKET_ERROR) {
            print_errno("Accepting connection from server failed!\n");
            continue;
          }
          // if parent terminates the child does the same
          prctl(PR_SET_PDEATHSIG, SIGHUP);
          messageLength = 0;
          char inBuffer[MESSAGE_SIZE];
          int readBytes = 0;
          memset(inBuffer, 0, sizeof(inBuffer));

          if((readBytes = read(inFd, &messageLength, sizeof(messageLength))) == SOCKET_ERROR)
            print_errno("unable to read message from server!\n");

          if((readBytes = read(inFd, inBuffer, messageLength)) == SOCKET_ERROR)
            print_errno("unable to read message from server!\n");

          if (readBytes > 0)
          {
            string stdString(inBuffer);
            cout << stdString << endl;
          }
          sleep(1);
          close(inFd);
          if (readBytes == 0)
            continue;
        }
        exit(0);
      }
    }
  }
}








void sig_handler(int sig)
{
  cout << "\nSIGTERM received, arrivederci!" << endl;
  if(socket_in_fd)
	close(socket_in_fd);
  if (outFd)
    close(outFd);
  exit(0);
}
