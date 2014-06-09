/*--------------------------------------------------*/
/* server.c                		             090614 */
/* Robert Muehlberger                   		 	*/
/*  												*/	
/* Client connect to server via localhost:3131 		*/
/*--------------------------------------------------*/
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVERPORT 3131 // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold

extern void ServerProcess(int in, int out);

#include <stdio.h>

/* user defined Signal handler! (avoids zombies) */
void waiter(){              
	int cpid, stat;
	/* wait for children */
	cpid = wait(&stat);
	
	/* reestablish signal handler */
	signal(SIGCHLD, waiter);
} // waiter

int main(int argc, char** argv){
	
  signal(SIGCHLD, waiter);            /* establish signal handler */     
	 
	struct sockaddr_in server;          /* represents the server */
	struct sockaddr_in client;          /* represents the client*/
  int sockfd, fd;                     /* file descriptors */
  uint client_len;                    /* information about the client */

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons (SERVERPORT);
  

  /* create socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		printf("Cannot get socket!\n");
		return 1;
	}
	
	int yes = 1;
	/* lose the pesky "address already in use" error message */
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	
	/* bind */ 
	if ((bind(sockfd, (struct sockaddr *) &server, sizeof(server))) == -1)
	{
		printf("Error while binding\n");
		return 1;
	}
  
	/* listen */
	listen(sockfd, BACKLOG);
	printf("Waiting for clients\n");
	
	int clients = 0;     
	/* start game */
  while(1){
		  
		 client_len = sizeof(client);
  
	   /* accept */
		 fd = accept(sockfd,(struct sockaddr *) &client,   &client_len); 
   	 printf("new client! Hostname: %s, Port: %i \n", 
		                    (char*)inet_ntoa((client.sin_addr)),
                    		(client.sin_port));
		 clients++;
		 printf("number of clients: %i\n", clients);
		 if (fd < 0){
		    printf("unable to accept client!\n");
		    return 1;
	   }
	   
		 /* for each client: create child process */ 
	   if (fork() == 0 ){
	      /* play the game! */
	      ServerProcess(fd,fd);
	      /* close "game" file descriptor (= fd of the child!) */
				close(fd);
				return 1;
	   }
		 else 
		    /* close "master" file descriptor (= fd of the father) */
	      close(fd);
     	
	 }
	/* close the socket */
	close(sockfd);
	
	return 0;
} // main

