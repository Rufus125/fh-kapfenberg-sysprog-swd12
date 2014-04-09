#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  if(argc < 3)
  {
    printf("usage: cpy SOURCEFILE DESTINATIONFILE\n");
    return EXIT_FAILURE;
  }

  int sfd;
  if((sfd = open(argv[1], O_RDONLY)) == -1)
  {
    perror("source file open");
    return EXIT_FAILURE;
  }

  struct stat sfd_stat;
  if(fstat(sfd, &sfd_stat) == -1)
  {
    perror("fstat");
    close(sfd);
    return EXIT_FAILURE;
  }

  int dfd;
  if((dfd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, sfd_stat.st_mode & 0777)) == -1)
  {
    perror("destination file open");
    close(sfd);
    return EXIT_FAILURE;
  }

  blksize_t block_size = sfd_stat.st_blksize;
  char* buff = (char*)calloc(1, sizeof(char) * block_size);
  int linesRead;
  while(linesRead = read(sfd, buff, block_size))
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