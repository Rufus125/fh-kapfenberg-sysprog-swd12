#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 4096

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cerr << "wrong number of arguments" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "copy: " << argv[1] << " to " << argv[2] << ": ";
	}

	int fd_source, fd_dest, bytesRead;
	char *buffer = NULL;
	unsigned long fileSize = 0; 
	unsigned long partSize = 0;
	
	fd_source = open(argv[1], O_RDONLY);	
	if(fd_source < 0)
	{
		perror(argv[1]);
		return 1;
	}
	
	remove(argv[2]);

	fd_dest = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd_dest < 0)
	{
		perror(argv[2]);
		return 1;
	}

	fileSize = lseek(fd_source, 0, SEEK_END);
	lseek(fd_source, 0, SEEK_SET);

	std::cout << fileSize << " bytes!" << std::endl;

	if(fileSize <= MAX_BUFFER_SIZE)
	{
		buffer = (char*) malloc(sizeof(char) * fileSize);
		read(fd_source, buffer, fileSize);
		
		if(write(fd_dest, buffer, fileSize) <= 0)
		{
			perror("write()");
			return 1;
		}

		if(buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
	}
	else
	{
		buffer = (char*) malloc(sizeof(char) * MAX_BUFFER_SIZE);
		partSize = MAX_BUFFER_SIZE;
		
		while(read(fd_source, buffer, partSize))
		{
			if(write(fd_dest, buffer, partSize) <= 0)
			{
				perror("write()");
				return 1;
			}

			if(buffer != NULL)
			{
				free(buffer);
				buffer = NULL;
			}

			partSize = fileSize - lseek(fd_source, 0, SEEK_CUR);

			if (partSize <= MAX_BUFFER_SIZE)
			{
				buffer = (char*) malloc(sizeof(char) * partSize);
			}
			else if(partSize > MAX_BUFFER_SIZE)
			{
				buffer = (char*) malloc(sizeof(char) * MAX_BUFFER_SIZE);
				partSize = MAX_BUFFER_SIZE;
			}
		}

		if(buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
	}
	
	if(lseek(fd_source, 0 , SEEK_CUR) != fileSize)
	{
		std::cout << "Error. Could not read whole file" << std::endl;
	}
	
	close(fd_source);
	close(fd_dest);
	
	return 0;
}
