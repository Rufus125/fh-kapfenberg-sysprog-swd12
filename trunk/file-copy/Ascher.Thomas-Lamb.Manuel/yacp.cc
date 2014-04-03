/* Thomas Ascher, Manuel Lamb */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define READ_BUFFER_SIZE 4096

int main(int argc, char** argv)
{
    if (argc != 3)
    {
    	fprintf(stderr, "Usage: yacp <source> <destination>\n");
    	return EXIT_FAILURE;
    }

    int fdIn = open(argv[1], O_RDONLY);
    if (fdIn < 0)
    {
    	perror("Could not open source");
    	return EXIT_FAILURE;
    }

    int fdOut = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fdOut < 0)
    {
    	perror("Could not create destination");
    	close(fdIn);
    	return EXIT_FAILURE;
    }

    char buffer[READ_BUFFER_SIZE] = "";

    ssize_t bytes = 0;
    int result = EXIT_SUCCESS;

    while ((bytes = read(fdIn, buffer, READ_BUFFER_SIZE)))
    {
    	if (bytes < 0)
    	{
    		perror("Read failed");
    		result = EXIT_FAILURE;
    		break;
    	}

    	if (write(fdOut, buffer, bytes) < 0)
    	{
    		perror("Write failed");
    		result = EXIT_FAILURE;
    		break;
    	}
    }

    close(fdIn);
    close(fdOut);

    return result;
}
