// Daniel Hoesele - Daniel Frech - SWD12

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

using namespace std;

const int BUFFER_SIZE = 4096;
const int FAILURE = 1;
const int SUCCESS = 1;


int main(int argc, char** argv)
{
    if (argc != 3) {
        cerr << "Program needs exactly 2 arguments" << endl;
        exit(FAILURE);
    }
    
    #ifdef DEBUG
    cout << "Source: " << argv[1] << endl;
    cout << "Destination: " << argv[2] << endl;
    #endif
    
    int source = open(argv[1], O_RDONLY);
    int dest = open (argv[2], O_WRONLY | O_CREAT | O_EXCL,  0666);
    
    if (source == -1 || !source) {
		perror("Failed to open source file");
		close(source);
		exit(FAILURE);
	}
	else if (dest == -1 || !dest) {
		perror("Failed to open destination file");
		close(source);
		close(dest);
		exit(FAILURE);
	}
	else {
		int *buffer[BUFFER_SIZE];
		int bytes = 0;
		
		while((bytes = read(source, buffer, BUFFER_SIZE)) != 0) {
			if(bytes != write(dest, buffer, bytes)) {
				perror("Could not write to destination file");
				close(source);
				close(dest);
				exit(FAILURE);
			}
		}
	}
	cerr << "Data successfully written to: " << argv[2] << endl;
	close(source);
	close(dest);
	return SUCCESS;
}
