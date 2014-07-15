/*
 * Common functions used by both the client and the server.
 * */

#ifndef lib_h
#define lib_h


/**
 * Constants
 * */
#define MESSAGE_SIZE 100
#define SOCKET_ERROR -1
#define REGISTER_TOKEN	"REGISTER"
#define EXIT_TOKEN "EXIT"
#define CLIENTS_FILE 	"clientOutFds.txt"
#define MAX_CLIENTS	100
#define SERVER_PORT	4711

#define REGISTER_SIZE 29
#define READ_BUFFER_LEN	REGISTER_SIZE + 1 


int create_socket();
int bind_socket(int socket_fd, int port);
int listen_on_socket(int socket_fd);
void print_errno(const char* message);
int getOwnIp (char* acIp);

#endif
