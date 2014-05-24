/*
 * STL - Simple Time cLient
 * Ascher, Lamb, Viehberger
 */

#include "sts.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int server_socket_fd;
	
	if (argc < 2)
	{
		fprintf(stderr, "simple time client\n");
		fprintf(stderr, "usage: std <host name>\n");
		return EXIT_FAILURE;
	}
	
	fprintf(stdout, "%s", sts_request_time_from_server(argv[1]));

	return EXIT_SUCCESS;
}
