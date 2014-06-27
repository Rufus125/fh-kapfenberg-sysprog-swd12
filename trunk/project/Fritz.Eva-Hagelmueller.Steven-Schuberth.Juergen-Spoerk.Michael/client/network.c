#include "network.h"

void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int get_temp(char *addr, int *temp)
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	char *temp_string = "temp\0";
	int error_count = 0;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
		
	if((rv = getaddrinfo(addr, PORT, &hints, &servinfo)) != 0)
	{
		perror("getaddrinfo:\n");
		return 1;
	}
	
	for(p = servinfo; p != NULL; p->ai_next)
	{
		if(error_count == 10)
		{
			freeaddrinfo(servinfo);
			return 1;
		}
	
		if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
		{
			perror("client socket");
			continue;
		}
		
		if(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("client connect");
			error_count++;
			continue;
		}
		
		break;
	}
	
	if(p == NULL)
	{
		perror("client: failed to connect\n");
		close(sockfd);
		return 1;
	}
	
	freeaddrinfo(servinfo);
			
	if (send(sockfd, temp_string, 5, 0) ==  -1)
	{
		perror("send");
		close(sockfd);
		exit(1);
	}

	if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
	{
		perror("recv");
		close(sockfd);
		exit(1);
	}
	
	buf[numbytes] = '\0';
	
	*temp = atoi(buf);
	
	close(sockfd);
	
	return 0;
}
