// Georg Schlagholz, SWD12

// simple out- and input
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// close/read/write
#include <unistd.h>

// open
#include <fcntl.h>

// error number output
#include <errno.h>
#include <string.h>

// file infos
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;

int main(int argc, char** argv)
{
    if (3 != argc) {
				cerr << "Usage: "<<argv[0] << " <SOURCE> <DESTINATION>" << endl;
				return 1;
    }
    else {
    	int source = open(argv[1], O_RDONLY);
    	if(source < 0){
    		perror("Could not open source");
    	}
    	int destination = open (argv[2], O_WRONLY | O_CREAT | O_EXCL,  0666);//rw everybody
    	if(destination < 0){
    	    		cerr << "destination: " << argv[2] <<" already exists"<< endl;
    	    		close(source);
    	    		return 3;
    	    	}
    	int *buffer[2048];
    	int numbytes = -1;
    	while((numbytes = read(source,buffer,2048)) !=0){
    		if(numbytes < 0){
    			perror("Read did not work out");
    								close(source);
    								close(destination);
    								return 5;
    		}
				if(numbytes != write(destination,buffer, numbytes)){
					cerr << "Write did not work out"<< endl;
					close(source);
					close(destination);
					return 4;
				}
    	}
			#ifdef DEBUG
						cerr << "Finished: wrote "<< numbytes << " Bytes from " << argv[1]<< " to "<< argv[2] <<endl;
			#endif
    	close(destination);
    	close(source);
    	return 0;
    }
}
