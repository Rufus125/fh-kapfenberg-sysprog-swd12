#ifndef NETWORK_H
#define NETWORK_H

#include "binary_temp.h"
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "9999"
#define MAXDATASIZE 8

void *get_in_addr(struct sockaddr *sa);
int get_temp(char *addr, int *temp);

#endif