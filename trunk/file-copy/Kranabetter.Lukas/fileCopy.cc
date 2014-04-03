/*
 * Exercise file copy, SysProg
 * Learning about system calls open, read and write
 *
 * @author: Lukas Kranabetter
 */
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

// Use namespace std for err streams, else they must be defined like std::cerr << "message" << std::endl
using namespace std;

#define BUFFER_SIZE 4096

/**
 * Program handle two command line arguments for file source and copy destination.
 * When the source is a valid existing file copy its content to the destination file.
 * Destination must be created, if it exists already method fails.
 *
 * @param argc int number of command line arguments
 * @param argv char** points to command line arguments, current path is given by default at argv[0]
 */
int main(int argc, char** argv)
{
	if(argc < 3)
	{
   	// cerr is standard output stream for errors
		cerr << "Missing Arguments" << endl;
		return -1;
	}

	// Source and destination paths
	char* source = argv[1];
	char* destination = argv[2];

	// open system call returns a integer value which is used to refer to it and close it when processing is done
	// See http://codewiki.wikidot.com/c:system-calls:open for informations about the oflags and mode parameters
	// int open(const char *path, int oflags, mode_t mode);
	int openSource = open(source, O_RDONLY);
	if(openSource == -1)
	{
		// You can use strerror() to get a human-readable string for the error number
		cerr << "Error opening source file: " << strerror(errno) << endl;
		return -1;
	}

	// Get source total bytes for progress
	struct stat st;
	stat(source, &st);
	int bytesTotal = st.st_size;

	int openDestination = open(destination,
															O_CREAT | O_EXCL | O_TRUNC | O_WRONLY,
															S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(openDestination == -1)
	{
		cerr << "Error opening destination file: " << strerror(errno) << endl;
		return -1;
	}

	cout << "Copy file " << source << " to " << destination << endl;

	// Define read buffer
	char buffer[BUFFER_SIZE];
	int bytesSource = 0;
	int bytesDestination = 0;
	int bytesProgress = 0;

	// Read first byte block with buffer size length into buffer
	bytesSource = read(openSource, buffer, BUFFER_SIZE);
	if(bytesSource == -1)
	{
		cerr << "Reading from source failed: " << strerror(errno) << endl;
		return -1;
	}

	// As long as source bytes to write are available go on
	while(bytesSource > 0)
	{
		// Write byte blocks from buffer to destination
		bytesDestination = write(openDestination, buffer, bytesSource);
		if(bytesDestination == -1)
		{
			cerr << "Writing to destination failed: " << strerror(errno) << endl;
			return -1;
		}

		// Show progress, use carriage return "\r" to display it always in the same output line
		bytesProgress = bytesProgress + bytesDestination;
		cout << "Processed " << bytesProgress << " bytes from " << bytesTotal << "\r";

		// Read further byte blocks into buffer
		bytesSource = read(openSource, buffer, BUFFER_SIZE);
		if(bytesSource == -1)
		{
			cerr << "Reading from source failed: " << strerror(errno) << endl;
			return -1;
		}
	}

	// Close the opened files with their file handles
	close(openSource);
	close(openDestination);
	// cout is standard output stream, write copy finished with a endl before to be sure its a separated output line
	cout << endl << "Finished" << endl;

	return 0;
}
