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
#define BUFFERSIZE 2048

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
    cerr << "ERROR while opening source file: ";
    cout << strerror(errno) << endl;
    return EXIT_FAILURE;
  }

  // open file to write to
  // mode is used for O_CREAT, if file doesn't exist it will be created with
  // read && write permissions
  int destinationFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, READWRITE);
  if(destinationFile == ERROR)
  {
    cerr << "ERROR while opening destination file: ";
    cout << strerror(errno) << endl;
    close(sourceFile);
    return EXIT_FAILURE;
  }

  ssize_t byte = 0;
  char buffer[BUFFERSIZE];

  // read from source file
  while((byte = read(sourceFile, buffer, BUFFERSIZE)))
      {
        // if read returns an error
        if(byte == ERROR)
        {
          cerr << "ERROR while reading source file: ";
          cout << strerror(errno) << endl;
          return closeFileWithError(sourceFile, destinationFile);
        }
        // write to destination file
        if(write(destinationFile, buffer, byte) == ERROR)
         {
           cerr << "ERROR while writing destination file: ";
           cout << strerror(errno) << endl;
           return closeFileWithError(sourceFile, destinationFile);
         }
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
