
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define READ_BUFFER_SIZE 4096

int main(int argc, char** argv)
{
    if (argc < 3)
    {
    	cerr << "Usage: yacp <source> <destination>" << endl;
    	return EXIT_SUCCESS;
    }

    int fdIn = open(argv[1], O_RDONLY);
    if (fdIn < 0)
    {
    	cerr << "Could not open source" << endl;
    	return EXIT_FAILURE;
    }

    int fdOut = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdOut < 0)
    {
    	cerr << "Could not open destination" << endl;
    	close(fdIn);
    	return EXIT_FAILURE;
    }

    char buffer[READ_BUFFER_SIZE];

    ssize_t bytes = 0;
    int result = EXIT_SUCCESS;

    while ((bytes = read(fdIn, buffer, READ_BUFFER_SIZE)))
    {
    	if (bytes < 0)
    	{
    		cerr << "Read failed" << endl;
    		result = EXIT_FAILURE;
    		break;
    	}

    	if (write(fdOut, buffer, bytes) < 0)
    	{
    		cerr << "Write failed" << endl;
    		result = EXIT_FAILURE;
    		break;
    	}
    }

    close(fdIn);
    close(fdOut);

    return result;
}
