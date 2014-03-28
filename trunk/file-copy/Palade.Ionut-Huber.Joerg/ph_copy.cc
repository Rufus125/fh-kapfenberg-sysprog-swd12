#include <iostream>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if(argc != 3){
		printf("Error! User 2 arguments!\n");
		return 1;
	}
	
	int fo = open(argv[1], O_RDONLY);
	printf("FileOpen: %i\n",fo);
	
	return 0;
}
