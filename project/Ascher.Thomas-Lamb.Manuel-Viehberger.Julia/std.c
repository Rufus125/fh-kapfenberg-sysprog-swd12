/*
 * STD - Simple Time Daemon
 * Ascher, Lamb, Viehberger
 */

#include "sts.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{	
	fprintf(stderr, "starting std\n");
	int pid = fork();
	if (pid == 0)
		sts_start_server();	
	return EXIT_SUCCESS;
}
