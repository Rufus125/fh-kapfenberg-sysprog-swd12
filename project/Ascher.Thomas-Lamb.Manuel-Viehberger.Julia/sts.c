/*
 * STS - Simple Time System, common protocol
 * Ascher, Lamb, Viehberger
 */

#include "sts.h"
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

#define STS_PORT 1337
#define READ_BUFFER_LEN 1024

static void sts_print_last_error(const char* message)
{
	fprintf(stderr, "STS: %s (%s)\n", message, strerror(errno));
}

static void sts_print_last_error_and_exit(const char* message)
{
	sts_print_last_error(message);
	exit(EXIT_FAILURE);
}

static char* sts_get_local_system_time()
{
	time_t epoch = time(NULL);
	return ctime(&epoch);
}

static int sts_create_socket()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		sts_print_last_error_and_exit("socket creation failed");
	return fd;
}

static void sts_bind_server_socket(int server_socket_fd)
{
	struct sockaddr_in server_address;
	memset(&server_address, sizeof(server_address), 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(STS_PORT);
	if (bind(server_socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
		sts_print_last_error_and_exit("socket to port binding failed"); 
}

static void sts_start_listening(int server_socket_fd)
{
	if (listen(server_socket_fd, SOMAXCONN) < 0)
		sts_print_last_error_and_exit("connection queue setup failed");	
}

static int sts_wait_for_client(int server_socket_fd)
{
	socklen_t client_adress_len = 0;
	struct sockaddr_in client_address;
	memset(&client_address, sizeof(client_address), 0);
	int client_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_address, &client_adress_len);
	if (client_socket_fd < 0)
		sts_print_last_error("accept of incoming connection failed");
	return client_socket_fd;
}

static void sts_process_client_request(int client_socket_fd)
{
	int pid = fork();
	if (pid < 0)
	{
		sts_print_last_error("forking of process for client request handling failed"); 
	}
	else if (pid == 0)
	{
		const char* local_time = sts_get_local_system_time();
		size_t len = strlen(local_time) + 1;
		if (write(client_socket_fd, local_time, sizeof(char) * len) < 0)
			sts_print_last_error_and_exit("sending date to client failed");
		exit(EXIT_SUCCESS);
	}
}

static void sts_dispatch_client_requests(int server_socket_fd)
{
	for (;;)
	{
		int client_socket_fd = sts_wait_for_client(server_socket_fd);
		if (client_socket_fd >= 0)
		{
			sts_process_client_request(client_socket_fd);
			close(client_socket_fd);
		}
	}	
}

void sts_start_server()
{
	int server_socket_fd = sts_create_socket();
	sts_bind_server_socket(server_socket_fd);
	sts_start_listening(server_socket_fd);
	sts_dispatch_client_requests(server_socket_fd);
	close(server_socket_fd);
}

static void sts_resolve_host(const char* host_name, struct sockaddr_in* server_address)
{
	struct hostent *host = gethostbyname(host_name);
	if (host == NULL)
		sts_print_last_error_and_exit("resolving of host name failed");

	memset(server_address, sizeof(server_address), 0);
	server_address->sin_family = AF_INET;
	server_address->sin_port = htons(STS_PORT);	
	memcpy(&(server_address->sin_addr.s_addr), host->h_addr, host->h_length);
}

static int sts_connect_to_server(const char* host_name)
{
	struct sockaddr_in server_address;
	memset(&server_address, sizeof(server_address), 0);
	sts_resolve_host(host_name, &server_address);
	int server_socked_fd = sts_create_socket();
	
	if (connect(server_socked_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) 
		sts_print_last_error_and_exit("connect to server failed");
	
	return server_socked_fd;
}

const char* sts_request_time_from_server(const char* host_name)
{
	int server_socked_fd = sts_connect_to_server(host_name);
	
	static char buffer[READ_BUFFER_LEN];
	memset(buffer, sizeof(char) * READ_BUFFER_LEN, 0);
	if (read(server_socked_fd, buffer, sizeof(char) * (READ_BUFFER_LEN - 1)) <= 0)
		sts_print_last_error_and_exit("reading time from server failed"); 

	close(server_socked_fd);

	return buffer;
}
