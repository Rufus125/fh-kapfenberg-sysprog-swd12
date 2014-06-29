#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <time.h>
#include <sys/wait.h>

#define SPI_DEVICE "/dev/spidev0.0"
 
int server_port = 9999;

int child_main(int cfd);
int get_temperature();
int spi_write_read(int fd, unsigned char *data, int length);
int rand_temp(int max_temp);

int main(int argc, char *argv[])
{
	int sfd;
	int cfd;
	struct sockaddr_in server_addr;
	socklen_t server_addr_len = sizeof(server_addr);

	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		return EXIT_FAILURE;
	}
		      
	memset(&server_addr, 0, server_addr_len);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);      
	server_addr.sin_addr.s_addr = INADDR_ANY;

	int optval = 1;
	if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
	{                                 
		perror("setsockopt");
	}             

	if(bind(sfd, (struct sockaddr*)&server_addr, server_addr_len) == -1)
	{
    perror("bind");                  
    close(sfd);
    return EXIT_FAILURE;
	}
        
	if(listen(sfd, SOMAXCONN) == -1)
	{
    perror("listen");
    close(sfd);
    return EXIT_FAILURE;
	}

	while ((cfd = accept(sfd, (struct sockaddr*) &server_addr, &server_addr_len)) != -1)
	{
    pid_t pid;
    if((pid = fork()) == -1)
    {
      perror("fork");
    }
    else if(pid == 0) //child process
    {
			close(sfd);
      return child_main(cfd);
    }
    close(cfd);
    wait(NULL);
	}

	if(cfd == -1) 
	{
    perror("accept");
    close(sfd);
    return EXIT_FAILURE;            
  }
    
  close(sfd);
  return EXIT_SUCCESS;
}

int child_main(int cfd)
{
  int32_t temp = get_temperature();

  uint32_t buff_size = 5;

  char *buff = (char*)calloc(buff_size, sizeof(char));
  size_t nRead = buff_size;
      
  while((nRead -= read(cfd, buff, nRead)) > 0);
  
  if(nRead == -1) 
  {
    perror("read");
    close(cfd);
    free(buff);
    return EXIT_FAILURE;
  }

  if(strncmp(buff, "temp", 4) == 0)
  {
    int i = 0;

    if(temp < 0)
    {
      temp *= -1;
      buff[0] = '-';
      i = 1;
    }

    for(; temp > 0; i++)
    {
      if(i >= buff_size)
 			{
        buff = (char*)realloc(buff, ++buff_size);
      }
      buff[i] = '0' + (temp % 10);
      temp /= 10;
    }

    buff_size = i + 1;
    buff = (char*)realloc(buff, buff_size);
    buff[buff_size - 1] = '\0';

    char *l = buff, *r = &buff[buff_size - 2];
    char tmp;
    if(buff[0] == '-')
      l++;

    while(r - l > 0)
    {
      tmp = *l;
      *l++ = *r;
      *r-- = tmp;
    }

    write(cfd, buff, buff_size);
  }

  free(buff);

  return EXIT_SUCCESS;
}

int spi_write_read(int fd, unsigned char *data, int length) 
{
  struct spi_ioc_transfer spi[length];
  int i; 
  int ret_val;  

  for(i = 0 ; i < length ; i++) 
  {
    spi[i].tx_buf = (unsigned long)(data + i);
    spi[i].rx_buf = (unsigned long)(data + i);
    spi[i].len = sizeof(*(data + i)) ;
    spi[i].delay_usecs = 0; 
    spi[i].speed_hz = 1000000;
    spi[i].bits_per_word = 8;
    spi[i].cs_change = 0;
  }

  ret_val = ioctl(fd, SPI_IOC_MESSAGE(length), &spi);
  
  if(ret_val < 0) 
  {
    perror("ioctl(SPI_IOC_MESSAGE)");
    exit(1);
  }

  return ret_val; 
}

int get_temperature()
{
  int spi_fd;
  
  if((spi_fd = open(SPI_DEVICE, O_RDWR)) == -1)
  {
    perror(SPI_DEVICE);
    return EXIT_FAILURE;
  }
  int value = 0; 
  int channel = 0;
  unsigned char data[3];

  data[0] = 1;
  data[1] = 0b10000000 |( ((channel & 7) << 4));
  data[2] = 0;

  spi_write_read(spi_fd, data, sizeof(data));
  
  value = 0;
  value = (((int)data[1])<< 8) & 0b1100000000;
  value |= (data[2] & 0xff);
  
  printf("rx_buf[0]=%d\n", data[0]);
  printf("rx_buf[1]=%d\n", data[1]);
  printf("rx_buf[2]=%d\n", data[2]);
  printf("a2dVal: %d\n\n", value);

  float voltage = ((5.5 / 1024) * value);
  //float degrees = ((value * 550) / (float)1024) - 25;

  //for testing:
  float degrees = rand_temp(130)-25;
  
  printf("volt: %f\n", voltage);
  printf("degr: %f\n\n", degrees);

  return degrees;
}

int rand_temp(int max_temp)
{
  int divisor = RAND_MAX/(max_temp+1);
  int retval;

  do
  {
    srand(time(NULL));
    retval = rand() / divisor;
  } while (retval > max_temp);

  return retval;
}
