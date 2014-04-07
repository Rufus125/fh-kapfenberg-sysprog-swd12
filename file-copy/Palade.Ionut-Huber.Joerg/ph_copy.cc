#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char** argv)
{
	if(argc != 3){
		cerr << "Error! Use 2 arguments!\n";
		return EXIT_FAILURE;
	}
	
	int fos = open(argv[1], O_RDONLY);
	if(fos < 0){
		perror ("Error while opening source file");
		return EXIT_FAILURE;
	}
	
	int fod = open(argv[2], O_EXCL | O_CREAT | O_WRONLY, 0644);
	if(fod < 0){
		perror ("Error while opening destination file");
		return EXIT_FAILURE;
	}
	
	
	char buf[1024] = "";
	ssize_t rd = 0;
	int fw;
	bool err_while_read_write = false;
	
	//read from source file and write do dest file
	while (true ) {
		
		//read byts from file in buffer
		rd = read(fos, buf, sizeof(*buf));
		
		//check for read errors
		if (rd < 0 )
		{
			perror ("The following read error occurred");
			err_while_read_write = true;
			break;
		}
			
		//try to write to file
		fw = write(fod, buf, sizeof(*buf));
		
		//check for file write error
		if ( fw < 0 )
		{
			perror ("The following write error occurred");
			err_while_read_write = true;
			break;		
		}
		
		//check for end of file
		if (rd == 0)
		{
			break;		
		}
		
		#ifdef DEBUG
			//print buffer value in debug modus
			printf("%s", buf);
		#endif
	}
	
	//close files
	close(fos);
	close(fod);
	
	if (err_while_read_write != 0)
	{
		return EXIT_FAILURE;;
	}
	else
	{
		return 0;
	}
	

}
