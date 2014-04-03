// Daniel Hoesele - Daniel Frech - SWD12

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

using namespace std;

const int SIZE = 4096;

int main(int argc, char** argv)
{
    if (argc != 3) {
        cerr << "Program need exactly 2 arguments" << endl;
        return 1;
    }
    
    cout << "Source: " << argv[1] << endl;
    cout << "Destination: " << argv[2] << endl;
    
    int source = open(argv[1], O_RDONLY);
    int dest = open (argv[2], O_WRONLY | O_CREAT | O_EXCL,  S_IRWXU);
    
    if (source == -1 || !source) {
		cerr << "Failed to open file: " << argv[1] << endl;
		cerr << strerror(errno) << endl;
		close(source);
		return 1;
	}
	else if (dest == -1 || !dest) {
		cerr << "Failed to open file: " << argv[2] << endl;
		cerr << strerror(errno) << endl;
		close(source);
		close(dest);
		return 1;
	}
	else {
		int *buffer[SIZE];
		int bytes = read(source, buffer, SIZE);
		if(bytes != write(dest, buffer, bytes)) {
			cerr << "Could not write to file: " << argv[2] << endl;
			cerr << strerror(errno) << endl;
			close(source);
			close(dest);
			return 1;
		}
	}
	cout << "Data successfully written to: " << argv[2] << endl;
	close(source);
	close(dest);
	return 0;
}
