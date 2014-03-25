// Mitteregger Christoph

#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;
#define ERROR -1
#define READWRITE 0600

int closeFileWithError(int source, int destination);

int main (int argc, char** argv)
{
  // checking whether input was in right format
  if(argc != 3)
  {
    cout << "Wrong Input, Please use:" << endl;
    cout << "./copyprog <source file> <destination file>" << endl;
    return EXIT_SUCCESS;
  }

  // if source file is same as destination file
  if(string(argv[1]) == string(argv[2]))
  {
    cout << "source file cannot be the same as destination file: try again" << endl;
    return EXIT_SUCCESS;
  }

  //open file to read from
  int sourceFile = open(argv[1], O_RDONLY);
  if(sourceFile == ERROR)
  {
    cerr << "ERROR while opening source file: " << strerror(errno) << endl;
    return EXIT_FAILURE;
  }

  // open file to write to
  // mode is used for O_CREAT, if file doesn't exist it will be created with
  // read && write permissions
  int destinationFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, READWRITE);
  if(destinationFile == ERROR)
  {
    cerr << "ERROR while opening destination file: " << strerror(errno) << endl;
    close(sourceFile);
    return EXIT_FAILURE;
  }

  // filling struct with information of destination file
  // e.g. total size, in bytes; needed for buffer size
  struct stat source;
  if(fstat(sourceFile, &source) == ERROR)
  {
    cerr << "ERROR getting Information of source file failed: ";
    cout << strerror(errno) << endl;
    return closeFileWithError(sourceFile, destinationFile);
  }

  // if the source file is empty, a warning will be displayed
  if(source.st_size == 0)
  {
    cout << "WARNING: source file is empty so ";
    cout << "destination file will be empty too ;-)" << endl;
  }
  ssize_t byte = 0;
  char buffer[source.st_size];

  // read from source
  if((byte = read(sourceFile, buffer, source.st_size)) == ERROR)
  {
    cerr << "ERROR while reading source file: ";
    cout << strerror(errno) << endl;
    return closeFileWithError(sourceFile, destinationFile);
  }
  // write to destination
  if(write(destinationFile, buffer, byte) == ERROR)
  {
    cerr << "ERROR while writing destination file: ";
    cout << strerror(errno) << endl;
    return closeFileWithError(sourceFile, destinationFile);
  }

  //filling struct with information of destination file
  struct stat destination;
  if(fstat(destinationFile, &destination) == ERROR)
  {
    cerr << "ERROR Getting Information of destination file failed: ";
    cout << strerror(errno) << endl;
    return closeFileWithError(sourceFile, destinationFile);
  }

  //if size of source and destination mismatch
  if(source.st_size != destination.st_size)
  {
    cerr << "ERROR: source and destination file size mismatch" << endl;
    return closeFileWithError(sourceFile, destinationFile);
  }

  close(sourceFile);
  close(destinationFile);
  return EXIT_SUCCESS;
}

int closeFileWithError(int source, int destination)
{
  close(source);
  close(destination);
  return EXIT_FAILURE;
}
