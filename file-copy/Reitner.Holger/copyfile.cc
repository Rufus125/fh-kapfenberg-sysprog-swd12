#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define READ_BUFFER_SIZE 4096

using namespace std;

bool file_exists(const char* filename)
{
  if (FILE* file = fopen(filename, "r"))
  {
    fclose(file);
    return true;
  }
  return false;
}

int main(int argc, char** argv) {
  // define vars for source and target file
  char* sourceFile = NULL;
  char* targetFile = NULL;
  
  // check given arguments
  if (argc > 1) {
      printf("Given parameters: %d\n", argc);
      for (int i=1; i<argc; i++)
          printf("   %s\n",argv[i]);

      sourceFile = argv[1];
      targetFile = argv[2];
      
      if (file_exists(targetFile)) {
      	fprintf(stderr, "Program terminated. Target file already exists!\n");
      	return 0;
	  }
  }
  else {
      fprintf(stderr, "No arguments given!\n");
      return 0;
  }

  char read_buffer[READ_BUFFER_SIZE];
  int targetFileHandle = -1;

  printf("Tyring to open file '%s'...\n", sourceFile);
  
  // open source file and get file handle or -1 if an error occurs
  int sourceFileHandle = open(sourceFile, O_RDONLY);
  if (sourceFileHandle == -1) {
    fprintf(stderr, "  Error opeing file '%s' with error code: %d\n",sourceFile,errno);
    return 0;
  }
  
  // define variable for bytes that are going to be read
  ssize_t sourceNoOfBytes;

  printf("Tyring to read from file '%s'...\n", sourceFile);

  //read the first time into buffer
  sourceNoOfBytes = read(sourceFileHandle, read_buffer, sizeof(read_buffer));
  if (sourceNoOfBytes != -1) {
    // go ahead and create the target file and start to read/write
    printf("Tyring to create file '%s'...\n", targetFile);

    // create a file with special options
    targetFileHandle = open(targetFile, O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);
    if (targetFileHandle == -1) {
      fprintf(stderr, "   Error creating file '%s' with error code: %d\n",targetFile,errno);
      close(sourceFileHandle);
      return 0;
    }
    ssize_t targetNoOfBytes;

    //read/write process
    do {
      //hint: when first entry, Bytes alread read
      printf("Bytes read: %d...\n", sourceNoOfBytes);

      printf("Writing to '%d' to '%s'\n", sourceNoOfBytes, targetFile);
      targetNoOfBytes = write(targetFileHandle, read_buffer, sourceNoOfBytes);
      printf("Bytes written: %d...\n", targetNoOfBytes);

	  // read again into read_buffer
      sourceNoOfBytes = read(sourceFileHandle, read_buffer, sizeof(read_buffer));
    } while(sourceNoOfBytes > 0); //do as along as data is available
  } else {
  	// error handling
    if (errno == EINTR)
      fprintf(stderr, "Error EINTR\n");
    else
      fprintf(stderr, "Error reading file '%s': %d\n", sourceFile, errno);
  }
  // close file handles
  close(targetFileHandle);
  close(sourceFileHandle);

  // exit program
  return 0;
}
