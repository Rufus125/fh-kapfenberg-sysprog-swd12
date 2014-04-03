/* Almer Patrick */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
    	cout << "You need to define the sourcefile and targetfile" << endl;
    	return 1;
    }

    cout << "sourcefile: " << argv[1] << " targetfile: " << argv[2] << endl;
	
	int sourcefile = open(argv[1], O_RDONLY);
	int targetfile = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR);
	
	if (!sourcefile || sourcefile < 0)
	{
		cerr << "Can't find file " << argv[1] << endl;
		close(sourcefile);
		close(targetfile);
		return 1;
	}
	
	if (!targetfile || targetfile < 0)
	{
		cerr << "Can't find file " << argv[2] << endl;
		close(sourcefile);
		close(targetfile);
		return 1;
	}
	
	int *buffer[4096];
	int bytes = read(sourcefile, buffer, 4096);
	
	if (bytes != write(targetfile, buffer, bytes))
	{
		cerr << "Unable to write data to file " << argv[2] << endl;
		close(sourcefile);
		close(targetfile);
		return 1;
	}
	
	cout << "File successfully copied to " << argv[2] << endl;
	close(sourcefile);
	close(targetfile);
	return 0;
}
