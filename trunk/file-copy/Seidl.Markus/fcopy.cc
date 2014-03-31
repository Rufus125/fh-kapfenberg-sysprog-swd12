#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
using namespace std;


int main(int argc, char** argv)
{
	if (argc < 3) {
        	cerr << "Not enough arguments given" << endl;
		return (-1);
	}
	int iSourceHandle = open(argv[1], O_RDONLY);
	if (iSourceHandle == -1) {
		handleFileError(argv[1]);
		return (-1);
	}

	int iMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int iDestHandle = open(argv[2], O_CREAT|O_EXCL|O_TRUNC|O_WRONLY, iMode);
	if (iDestHandle == -1) {
		if (errno == EEXIST ) {
			handleFileError(argv[2]);
			cerr << "File " << argv[2] << " already exists." << endl;
		}
		return (-1);
	}
	const int buf_size = 10;
	const char buffer[buf_size] = {};
	int bytes_read = 0;
	int bytes_written = 0;
	cout << argv[1] << " wird nach " << argv[2] << " kopiert.   ";
	bytes_read = read (iSourceHandle, (void*) buffer, buf_size);
	if (bytes_read == -1) {
		cerr << "read operation failed: errno = " << errno << endl;
	}

	while (bytes_read > 0) {
	
		bytes_written = write (iDestHandle, (void*)buffer, bytes_read);	
		if (bytes_written == -1) {
			cerr << "write operation failed: errno = " << errno << endl;
			return (-1);
		}
		bytes_read = read (iSourceHandle, (void*)buffer, buf_size);
		if (bytes_read == -1) {
			cerr << "read operation failed: errno = " << errno << endl;
			return (-1);
		}
	}
	close(iDestHandle);
	close(iSourceHandle);
	cout << "DONE" << endl;
	return 0;
}
