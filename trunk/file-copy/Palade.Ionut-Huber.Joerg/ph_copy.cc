#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc != 3){
		printf("Error! User 2 arguments!\n");
		return 1;
	}
	
	int fos = open(argv[1], O_RDONLY);
	printf("FileOpen Source: %i\n",fos);
	
	int fod = open(argv[2], O_TRUNC | O_CREAT | O_WRONLY);
	printf("FileOpen Destination: %i\n",fos);
	
	char buf[1024] = "";
	ssize_t rd = 0;
	
	//file write result
	int fw;
	
	while (true ) {
		rd= read(fos, buf, sizeof(*buf));
		
		//check for read errors
		if (rd < 0 )
		{
			printf("%s", buf);
			break;
		}
			
		//try to write to file
		fw = write(fod, buf, sizeof(*buf));
		
		//check for file write error
		if ( fw < 0 )
		{
			printf("\nfile write error");
			break;		
		}
		
		//check for end of file
		if (rd == 0)
		{
			printf("\nread end buf value %s", buf);
			break;		
		}
		
		printf("%s", buf);
	}
	
	close(fos);
	close(fod);
	
	return 0;
}
