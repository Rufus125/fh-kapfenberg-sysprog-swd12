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
	
	int fo = open(argv[1], O_RDONLY);
	printf("FileOpen: %i\n",fo);
	
	char buf[1024] = "";
	ssize_t rd = 0;
	
	while (true ) {
		rd= read(fo, buf, sizeof(*buf));
		
		//check for read errors
		if (rd < 0 )
		{
			printf("%s", buf);
			break;
		}
		
		//check for end of file
		if (rd == 0)
		{
			printf("\nread end buf value %s", buf);
			break;		
		}
		
		//try to write to file

		
		printf("%s", buf);
	}
	
	return 0;
}
