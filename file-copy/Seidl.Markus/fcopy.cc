#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
using namespace std;


int main(int argc, char** argv)
{
	if (argc < 3) {
        	cerr << "Not enough arguments given" << endl;
		return (EXIT_FAILURE);
	}
	int iSourceHandle = open(argv[1], O_RDONLY);
	if (iSourceHandle == -1) {
		perror("source file");
		return (EXIT_FAILURE);
	}

	int iMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int iDestHandle = open(argv[2], O_CREAT|O_EXCL|O_TRUNC|O_WRONLY, iMode);
	if (iDestHandle == -1) {
		perror("destination file");
		return (EXIT_FAILURE);
	}
	const int buf_size = 1000;
	const char buffer[buf_size] = {};
	int bytes_read = 0;
	int bytes_written = 0;
	bytes_read = read (iSourceHandle, (void*) buffer, buf_size);
	if (bytes_read == -1) {
		perror("read()"); 
		return (EXIT_FAILURE);
	}

	while (bytes_read > 0) {
	
		bytes_written = write (iDestHandle, (void*)buffer, bytes_read);	
		if (bytes_written == -1) {
			perror("write()"); 
			return (EXIT_FAILURE);
		}
		bytes_read = read (iSourceHandle, (void*)buffer, buf_size);
		if (bytes_read == -1) {
			perror("read()"); 
			return (EXIT_FAILURE);
		}
	}
	close(iDestHandle);
	close(iSourceHandle);
	return EXIT_SUCCESS;
}
