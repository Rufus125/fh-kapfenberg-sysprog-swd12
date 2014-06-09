/*--------------------------------------------------*/
/* client.c                		             090614 */
/* Robert Muehlberger                   		 	*/
/*  												*/	
/* Client connect to server via localhost:3131 		*/
/*--------------------------------------------------*/

#include <signal.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>

/* POLL */
void comm(int tfd , int nfd){
   int n, i;
   struct pollfd pfd [2];
   char buf [256];
   pfd [0]. fd = tfd; /* terminal */
   pfd [0]. events = POLLIN ;
   pfd [1]. fd = nfd; /* network */
   pfd [1]. events = POLLIN ;
   for (;;) {
      /* Wait for events to occur. */
      if ( poll(pfd , 2, -1) < 0) {
         printf (" poll failed \n");
         break ;
      }
  
	    /* Check each file descriptor. */
      for (i = 0; i < 2; i++) {
         /* If an error occurred , just return . */
         if (pfd[i]. revents&( POLLERR| POLLHUP| POLLNVAL))
            return ;

         /* If there are data present , read them from */
				 /* one file descriptor and write them to the other one. */

         if (pfd[i]. revents& POLLIN ) {
            n = read(pfd[i].fd , buf , sizeof (buf));
            if (n > 0) {
               write( pfd[1-i].fd , buf , n); 
            } 
						else {
               if (n < 0)
               printf (" read failed \n");
               return ;
            }
         }
      }
   }
} // comm


int main(int argc, char** argv){
	
  struct hostent * serverEntry = NULL ;    /* represents host and server */
  struct sockaddr_in client ;              /* client socket */

	int port, sockfd ;                       /* port and socket */
	
	/* check parameters */
	if (argc != 3){
		printf("Wrong number of arguments!\n");
		printf("USAGE: %s host portnumber\n",argv[0]);
		return 1;
	}
	
	if (atoi(argv[2]) < 0){
	  printf("invalid port\n");
		printf("USAGE: %s host portnumber\n",argv[0]);
		return 1;
	}
	
	/* error with host name (invalid) */
	if ((serverEntry = gethostbyname( argv [1])) == NULL) {
		printf ("error while gethostbyname");
		exit (1);
	}
	
	serverEntry = gethostbyname ( argv [1]) ;
	
	
	
	/* get port for the game */
	port = atoi(argv[2]);
	
	/* open socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* inet_addr : converts string into proper address for IN_ADDR */
	client . sin_family = AF_INET ;

	/* inet_ntoa : convert internet host address to a dotted */
	client.sin_addr.s_addr = inet_addr ( inet_ntoa (*( struct in_addr *) serverEntry -> h_addr ));
	client . sin_port = htons ( atoi ( argv [2]) );

	 /* call connect -- TODO : check for error */
	 connect ( sockfd , ( struct sockaddr *)&client , sizeof ( client ));
	
	/* game loop */
	while(1){
	   
			char Buff[80];

      /* read from socket (= read from server)*/
			read(sockfd, Buff, sizeof(Buff));
	   
			/* check if game is over */
			if (strcmp("Game over",Buff) == 0 || strcmp("You won!",Buff) == 0)
			   return 0;
				 
			/* write server message to screen */
			write(1, Buff, strlen(Buff));
	    
      /* read user input */
			read(0, Buff, sizeof(Buff));
			
			/* write to socket (= write to server) */
	    write(sockfd, Buff, strlen(Buff));
    } // while
	 
	return 0;
} // main
