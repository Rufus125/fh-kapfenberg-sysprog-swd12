#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <utility>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>
#include "../lib/lib.h"

using namespace std;

int socket_fd = 0;
int outFd = 0;
int inFd = 0;
bool checkRegisteredClients(char const* ipPort);
bool writeClient(char const* ipPort);
void sig_handler(int sig);
void removeClient(string ipPort);
bool writeTempClient(char const* ipPort);

int main (int argc, char** argv)
{
  //remove("clientTemp.txt")
  //remove("clientOutFds.txt");

  /* catch Ctrl+C  SIGNAL */
  signal(SIGINT, sig_handler);

  /* create socket */
  if ((socket_fd = create_socket()) == SOCKET_ERROR)
    return EXIT_FAILURE;

  /* Bind socket to port. */
  if ((bind_socket(socket_fd, SERVER_PORT)) == SOCKET_ERROR)
    return EXIT_FAILURE;

  /* Activate socket for incoming connections. */
  if((listen_on_socket(socket_fd)) == SOCKET_ERROR)
    return EXIT_FAILURE;

  /* Get own IP address. */
  char ownIp[INET_ADDRSTRLEN] = {};
  if (getOwnIp(ownIp) < 1)
  {
    fprintf(stderr,"Couldn't obtain own ip!\n");
    return EXIT_FAILURE;
  }


  /* Accept client connections. */
  while (42)

  {
    if ((inFd = accept(socket_fd, 0, 0)) == SOCKET_ERROR)
    {
      print_errno("accept socket failed");
      continue;
    }
    else
    {
      pid_t pid = fork();
      if (pid > 0)//parent
      {
        /* Close fd's in parent process since reading and writing messages after the initial register */
        close(inFd);
      }else if (pid == 0)//client
      {
        bool knownClient;
        bool registeredClient = false;
	while (42)
	{
          /* Read data from socket. */
          char inBuffer[MESSAGE_SIZE];
          int readBytes = 0;
          memset(inBuffer, 0, sizeof(inBuffer));

          unsigned int length;

          readBytes = read(inFd, &length, sizeof(length));
          if (readBytes == SOCKET_ERROR)
          {
            print_errno("Read socket failed\n");
            close(inFd);
            continue;
          }

          readBytes = read(inFd, inBuffer, length);

          if (readBytes == SOCKET_ERROR)
          {
            print_errno("Read socket failed\n");
            close(inFd);
            continue;
          }

          if (readBytes == 0)
            continue;

          string reg;
          string ipPort;
          string ip;
          string port;

          string clientString(inBuffer);// needed for Register message
          string searchExit(inBuffer);// needed for exit message

          string exit = searchExit.substr(0, 4);
          if(exit.compare("EXIT") == 0)
          {
            ipPort = searchExit.substr(4);
            removeClient(ipPort);
            return 0;
            //continue;
          }

          // check whether first message was a register message
          if (registeredClient == false)
          {
            reg = clientString.substr(0, 8);
            int indexOfSeparator = clientString.find(":");
            ipPort = clientString.substr(8);
            ip = clientString.substr(8, indexOfSeparator - sizeof(REGISTER_TOKEN) +1 );
            port = clientString.substr(indexOfSeparator + 1);
            knownClient = checkRegisteredClients(ipPort.c_str());
            if (reg.compare(REGISTER_TOKEN) == 0 && knownClient == false)
            {
              writeClient(ipPort.c_str());
              registeredClient = true;
              //continue;
            }else if (reg.compare(REGISTER_TOKEN))
            {
              continue;
            }
          }

          if (registeredClient == true)
          {
            string zeile;
            FILE* fin = fopen("clientOutFds.txt", "r");
            int result = flock(fileno(fin), LOCK_EX);
            if (result)
            {
              print_errno("failed to lock file");
              continue;
            }

            char line[MESSAGE_SIZE];
            int counter = 0;

            while(fgets(line,MESSAGE_SIZE, fin))	//eof() liefert 'true' wenn Dateiende erreicht
            {
              zeile = line;
              int indexOfSeparator = zeile.find('\n');
              zeile = zeile.substr(0,indexOfSeparator);
              indexOfSeparator = zeile.find(":");
              ip = zeile.substr(0,indexOfSeparator);
              port = zeile.substr(indexOfSeparator + 1);

              char clientaddr[INET_ADDRSTRLEN];

              outFd = create_socket();
              struct sockaddr_in client;
              memset(&client, 0, sizeof(client));       /* Clear struct */
              client.sin_family = AF_INET;                  /* Internet/IP */
              inet_pton(AF_INET,ip.c_str(), &(client.sin_addr));
              client.sin_port = htons(atoi(port.c_str()));       /* server port */


              if (connect(outFd, (struct sockaddr *) &client, sizeof(client)) == SOCKET_ERROR)
              {
                print_errno("Connecting to client failed!");
                //close(outFd);
                continue;
              }

              int writeBytes = 0;
              writeBytes = send(outFd, &length, sizeof(length),0);
              if (writeBytes == SOCKET_ERROR)
              {
                print_errno("Write in socket failed\n");
                close(inFd);
                close(outFd);
                continue;
              }

              writeBytes = send(outFd, inBuffer, length,0);

              if (writeBytes == SOCKET_ERROR)
              {
                print_errno("Write in socket failed\n");
                close(inFd);
                close(outFd);
                continue;
              }
              close(outFd);
            }
            result = flock(fileno(fin),LOCK_UN);
            if (result)
            {
              print_errno("failed to unlock file");
              continue;
            }
            fclose(fin);
          }
          sleep(1);
	}
	exit(0);
      }
    }
    sleep(1);
  }
  exit(0);
}

// remove the client frome the list to connect to
void removeClient(string ipPort)
{
  int fileFd, retval;

  string zeile;
  FILE* fin = fopen("clientOutFds.txt", "r");
  int result = flock(fileno(fin), LOCK_EX);
  if (result)
  {
    print_errno("failed to lock file");
  }

  ssize_t writebytes;
  char line[MESSAGE_SIZE];

  int counter = 0;
  while(fgets(line,MESSAGE_SIZE, fin))	//eof() liefert 'true' wenn Dateiende erreicht
  {

    zeile = line;
    int indexOfSeparator = zeile.find('\n');
    zeile = zeile.substr(0,indexOfSeparator);

    if(zeile.compare(ipPort))
      writeTempClient(zeile.c_str());
    counter++;
  }


  result = flock(fileno(fin),LOCK_UN);
  if (result)
  {
    print_errno("failed to unlock file");
  }
  fclose(fin);

  if (counter == 1)
    remove("clientOutFds.txt");
  else
    rename("clientTemp.txt", "clientOutFds.txt");

}

bool checkRegisteredClients(char const* ipPort)
{
  int fileFd, retval;
  bool found_client = true;

  //open client file for read
  if((fileFd = open("clientOutFds.txt",O_RDONLY | O_APPEND)) == SOCKET_ERROR)
    print_errno("file open failed");

  //lock file for reading
  if((retval = flock(fileFd, LOCK_EX)) == SOCKET_ERROR )
    print_errno("failed to lock file");

  char Buffer[2235] = {};
  ssize_t readbytes;

  readbytes = read(fileFd,  &Buffer, sizeof(Buffer));

  char * pch;
  pch = strstr (Buffer, ipPort);

  if (pch == NULL)
  {
    found_client = false;
  }

  if ((retval = flock(fileFd, LOCK_UN)) == SOCKET_ERROR)
    print_errno("failed to unlock file");

  close(fileFd);
  return found_client;
}

bool writeClient(char const* ipPort)
{
  int fileFd, retval;
  //open client file for read
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  if((fileFd = open("clientOutFds.txt",O_CREAT | O_WRONLY | O_APPEND, mode) ) == SOCKET_ERROR)
    print_errno("file open failed");

  //lock file for reading
  if((retval = flock(fileFd, LOCK_EX)) == SOCKET_ERROR )
    print_errno("failed to lock file");

  ssize_t writebytes;

  char *client = new char(strlen(ipPort +1 ));

  strncpy(client,ipPort,strlen(ipPort));
  client[strlen(ipPort)] = '\n';

  writebytes = write(fileFd,  client, strlen(client));

  if ((retval = flock(fileFd, LOCK_UN)) == SOCKET_ERROR)
    print_errno("failed to unlock file");

  close(fileFd);
  return true;
}

bool writeTempClient(char const* ipPort)
{
  int fileFd, retval;
  //open client file for read
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  if((fileFd = open("clientTemp.txt",O_CREAT | O_WRONLY | O_APPEND, mode) ) == SOCKET_ERROR)
    print_errno("file open failed");

  //lock file for reading
  if((retval = flock(fileFd, LOCK_EX)) == SOCKET_ERROR )
    print_errno("failed to lock file");

  ssize_t writebytes;

  char *client = new char(strlen(ipPort +1 ));

  strncpy(client,ipPort,strlen(ipPort));
  client[strlen(ipPort)] = '\n';

  writebytes = write(fileFd,  client, strlen(client));

  if ((retval = flock(fileFd, LOCK_UN)) == SOCKET_ERROR)
    print_errno("failed to unlock file");

  close(fileFd);
  return true;
}



void sig_handler(int sig)
{
  cout << "\nSIGTERM received, arrivederci!" << endl;
  if(socket_fd)
    close(socket_fd);
  if (inFd)
    close(inFd);
  if (outFd)
    close(outFd);
  exit(0);
}
