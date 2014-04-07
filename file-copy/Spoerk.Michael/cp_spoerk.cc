#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cerr << "wrong number of arguments. cp_spoerk SOURCE DESTINATION" << std::endl;
		return 1;
	}

	int fd_source, fd_dest, bytesRead;
	char *buffer = NULL;
	
	fd_source = open(argv[1], O_RDONLY | O_EXCL);	
	if(fd_source < 0)
	{
		perror("could not open source file");
		return 1;
	}
	
	fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644);
	if(fd_dest < 0)
	{
		perror("could not open destination file");
		return 1;
	}

	buffer = (char*) malloc(sizeof(char) * BUFFER_SIZE);	
	if(buffer == NULL)
	{
		std::cerr << "could not allocate buffer memory" << std::endl;
		return 1;
	}

	while(bytesRead = read(fd_source, buffer, BUFFER_SIZE))
	{
		if(bytesRead <= 0)
		{
			perror("could not read source file");
			return 1;
		}

		if(!write(fd_dest, buffer, bytesRead))
		{
			perror("could not write destination file");
			return 1;
		}
	}

	if(buffer != NULL)
	{
		free(buffer);
	}
	
	close(fd_source);
	close(fd_dest);
	
	return 0;
}
