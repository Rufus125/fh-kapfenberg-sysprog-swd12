/* Exercise 1,
   "cp" clone shell program,
   Temmel Philipp
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE_IN_BYTE 4096

using namespace std;

/* Forward declaration for helper function to avoid code redundancy. */
int closeFilesAndReturn(int fdIn, int fdOut, int returnValue);

int main(int argc, char** argv) {

	/* Verify if user input is correct (i.e. number of args must be 3). */
    if (argc != 3) {
    	cerr << "Incorrect usage of program. Try out:" << endl << "filecopy <source> <destination>" << endl;

    	return EXIT_FAILURE;
    }

    /* Verify that source file and destination file are not the same. */
    if (string(argv[1]).compare(string(argv[2])) == 0) {
    	cerr << "Incorrect usage of program. Source file and destination file need to be different!" << endl;

    	return EXIT_FAILURE;
    }

    /* Try to open source file with readOnly-Access and exit upon failure. */
    int fdIn = open(argv[1], O_RDONLY);

    if (fdIn == -1) {
      cerr << "Failed to open source file due to: " << strerror(errno) << endl;
      
      return EXIT_FAILURE; 	
    }

    /* Open destination file for writing purposes (permissions: rw-r--r--). If the file doesn't exist, create it.
       Note: Upon failure the ingoing file descriptor has to be closed to free up ressources.
     */
    int fdOut = open(argv[2], O_CREAT | O_WRONLY, 0666);

    if (fdOut == -1) {
      cerr << "Failed to open destination file due to: " << strerror(errno) << endl;
      
      close(fdIn);

      return EXIT_FAILURE;
    }

    /* Read file content from source file in blocks of BUFFER_SIZE_IN_BYTE and write the buffered content to the destination file until no content is left or an error occurs. */
    ssize_t bytesRead = 0;
    char fileBuffer[BUFFER_SIZE_IN_BYTE] = "";

    while (bytesRead = read(fdIn, fileBuffer, BUFFER_SIZE_IN_BYTE)) {
      if (bytesRead == -1) {
      	cerr << "An error occurred while reading from source file: " << strerror(errno) << endl;
      	
      	closeFilesAndReturn(fdIn, fdOut, EXIT_FAILURE);
      }

      if (write(fdOut, fileBuffer, bytesRead) == -1) { // Note: We write to destination file and check for error at once here.
        cerr << "An error occurred while writing to destination file: " << strerror(errno) << endl;

      	closeFilesAndReturn(fdIn, fdOut, EXIT_FAILURE);
      }
    }

    /* Clean up ressources after everything went fine. */
    closeFilesAndReturn(fdIn, fdOut, EXIT_SUCCESS);
}

/* Close fdIn and fdOut and return the specified value for easy ressource handling and program termination. */
int closeFilesAndReturn(int fdIn, int fdOut, int returnValue) {
  close(fdIn);
  close(fdOut);

  return returnValue;
}