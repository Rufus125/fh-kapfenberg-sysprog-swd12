// Daniel Hösele - 1210418031 - SWD12

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

const int size = 2048;

int main(int argc, char** argv)
{
    if (argc != 3) {
        cerr << "Program need exactly 2 arguments" << endl;
        return 1;
    }
    
    cout << "Source: " << argv[1] << endl;
    cout << "Destination: " << argv[2] << endl;
    
    int source = open(argv[1], O_RDONLY);
    int dest = open (argv[2], O_WRONLY | O_CREAT | O_EXCL,  S_IRUSR);
    
    if (source < 0 || !source) {
		cerr << "No such file: " << argv[1] << endl;
		close(source);
		return 1;
	}
	else if (dest < 0 || !dest) {
		cerr << "No such file: " << argv[2] << endl;
		close(source);
		close(dest);
		return 1;
	}
	else {
		int *buffer[size];
		int bytes = read(source, buffer, size);
		if(bytes != write(dest, buffer, bytes)) {
			cerr << "Could not write to file: " << argv[2] << endl;
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
