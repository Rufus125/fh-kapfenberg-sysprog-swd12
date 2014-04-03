#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
  if(argc < 3)
  {
    printf("usage: cpy SOURCEFILE DESTINATIONFILE");
    return EXIT_FAILURE;
  }

  int sfd;
  
  if((sfd = open(argv[1], O_RDONLY)) == -1)
  {
    perror("source file open");
    return EXIT_FAILURE;
  }

  int dfd;

  if((dfd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL)) == -1)
  {
    perror("destination file open");
    close(sfd);
    return EXIT_FAILURE;
  }

  char* buff = (char*)calloc(1, sizeof(char) * 100);

  int linesRead;

  while((linesRead = read(sfd, buff, 100)) != 0)
  {
    if(linesRead == -1 || write(dfd, buff, linesRead) == -1)
    {
      perror("read/write");
      close(sfd);
      close(dfd);
      free(buff);
      return EXIT_FAILURE;
    }
  }

  close(sfd);
  close(dfd);
  free(buff);
  
  return EXIT_SUCCESS;
}
