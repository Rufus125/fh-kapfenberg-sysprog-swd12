#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main (int argc, char** argv )
{
	if(argc != 3)
	{
		cerr << "worng parameters, use:" << endl;
		cerr << "./yacp <src> <dest>" << endl;
		return EXIT_FAILURE;
	}
	
	if(string(argv[1]) == string(argv[2]))
	{
		cerr << "src and dest are the same, thats not working!" << endl;
		return EXIT_FAILURE;
	}
	
	int src = open(argv[1], O_RDONLY);
	if(src < 0){
		perror ("couldn't open src");
		return EXIT_FAILURE;
	}
	
	int dest = open(argv[2], O_CREAT | O_WRONLY | O_EXCL, 0666);
	if(dest < 0){
		perror ("couldn't open dest");
		return EXIT_FAILURE;
	}
	
	int *buf[2048];
    int bytes = -1;
    while((bytes = read(src, buf, 2048)) !=0){
    	if(bytes < 0)
    	{
			cerr << "couldn't write" << endl;
    		close(src);
    		close(dest);
			return EXIT_FAILURE;
    	}
		if(bytes != write(dest, buf, bytes)){
			cerr << "couldn't write" << endl;
			close(src);
			close(dest);
			return EXIT_FAILURE;
		}
    }
    close(dest);
    close(src);
    return EXIT_SUCCESS;
}
