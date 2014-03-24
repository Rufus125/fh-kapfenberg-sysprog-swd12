// Mitteregger Christoph

#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
#define ERROR -1
#define READWRITE 0600

int
main (int argc, char** argv)
{
  // checking whether input was in right format
  if (argc != 3)
    {
      cout << "Wrong Input, Please use:" << endl;
      cout << "./copyprog <source file> <destination file>" << endl;
      return EXIT_SUCCESS;
    }

  //open file to read from
  int sourceFile = open (argv[1], O_RDONLY);
  if (sourceFile <= ERROR)
    {
      cout << "ERROR: File to read could not be opened" << endl;
      return EXIT_FAILURE;
    }

  // open file to write to
  // mode is used for O_CREAT, if file doesn't exist it will be created with
  // read && write permissions
  int destinationFile = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, READWRITE);
  if (destinationFile <= ERROR)
    {
      cout << "ERROR: File to write to could not be opened" << endl;
      close (sourceFile);
      return EXIT_FAILURE;
    }

  // filling struct with information of destination file
  // e.g. total size, in bytes; needed for buffer size
  struct stat source;
  if (fstat (sourceFile, &source) == -1)
    {
      cout << "ERROR: Getting Information of source file failed" << endl;
      return EXIT_FAILURE;
    }

  // if the source file is empty, a warning will be displayed
  if (source.st_size == 0)
    {
      cout << "WARNING: source file is empty but ";
      cout << "destination file will be created anyway" << endl;
    }
  ssize_t bytes = 0;
  char buffer[source.st_size];

  // writing the data from source to destination file
  while ((bytes = read (sourceFile, buffer, source.st_size)))
    {
      write (destinationFile, buffer, bytes);
    }

  //filling struct with information of destination file
  struct stat destination;
  if (fstat (destinationFile, &destination) == -1)
    {
      cout << "ERROR: Getting Information of destination file failed" << endl;
      return EXIT_FAILURE;
    }

  //if size of source and destination mismatch
  if (source.st_size != destination.st_size)
    {
      cout << "ERROR: source and destination file size mismatch" << endl;
      return EXIT_FAILURE;
    }

  close (sourceFile);
  close (destinationFile);
  return EXIT_SUCCESS;
}
