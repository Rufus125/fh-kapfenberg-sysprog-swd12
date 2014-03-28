// Georg Schlagholz, SWD12

// simple out- and input
#include <iostream>
#include <stdlib.h>

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
    		cerr << "Could not open source" <<  argv[1] << endl;
    		close(source);
    		return 2;
    	}
    	int destination = open (argv[2], O_WRONLY | O_CREAT | O_EXCL,  S_IRUSR);
    	if(destination < 0){
    	    		cerr << "destination: " << argv[2] <<" already exists"<< endl;
    	    		close(source);
    	    		close(destination);
    	    		return 3;
    	    	}
    	int *buffer[2048];
    	int numbytes = read(source,buffer,2048);
    	if(numbytes != write(destination,buffer, numbytes)){
    		cerr << "Write did not work out"<< endl;
    		close(source);
				close(destination);
				return 4;
    	}
    	cout << "Finished: wrote "<< numbytes << " Bytes from " << argv[1]<< " to "<< argv[2] <<endl;
    	close(destination);
    	close(source);
    	return 0;
    }
}
