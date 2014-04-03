#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

const int err_arguments = 1;
const int err_openfile = 2;
const int err_writefile = 3;
const int err_readfile = 4;

//TODO:
//immer exit code 1 retur geben bei fehler
//perror implementieren
//"Wenn SOURCE existiert und DESTINATION nicht extistiert kopiert es...
// O_EXCL in den open Command implementieren
// permission 0666

int main(int argc, char** argv)
{
	if(argc != 3){
		cout << "Error! Use 2 arguments!\n";
		return err_arguments;
	}
	
	int fos = open(argv[1], O_RDONLY);
	if(fos < 0){
		cerr << "Error! Couldn't open source file: " << argv[1] << endl;
		return err_openfile;
	}
	
	int fod = open(argv[2], O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IXUSR);
	if(fod < 0){
		cerr << "Error! Couldn't open destination file: " << argv[2] << endl;
		return err_openfile;
	}
	
	
	char buf[1024] = "";
	ssize_t rd = 0;
	int fw;
	int err_while_read_write = 0;
	
	//read from source file and write do dest file
	while (true ) {
		
		//read byts from file in buffer
		rd = read(fos, buf, sizeof(*buf));
		
		//check for read errors
		if (rd < 0 )
		{
			cerr << "Error! Couldn't read from source file: " << argv[1] << endl;
			err_while_read_write = err_readfile;
			break;
		}
			
		//try to write to file
		fw = write(fod, buf, sizeof(*buf));
		
		//check for file write error
		if ( fw < 0 )
		{
			cerr << "Error! Couldn't not write to destination file: " << argv[2] << endl;
			err_while_read_write = err_writefile;
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
		printf("error while executing %d\n", err_while_read_write);
		return err_while_read_write;
	}
	else
	{
		printf("file copy succed\n");
		return 0;
	}
	

}
