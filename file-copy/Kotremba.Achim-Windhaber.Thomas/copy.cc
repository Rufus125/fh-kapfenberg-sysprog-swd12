/* Kotremba Achim, Windhaber Thomas */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unstd.h>
#include <fcntl.h>

using namespace std;

const int SIZE 2048;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
    	cout << "You need to define the source and target" << endl;
    	return 1;
    }

    cout << "source: " << argv[1] << " Target: " << argv[2] << endl;
	
	int source = open(argv[1], O_RDONLY);
	int target = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR);
	
	if (!source || source < 0)
	{
		cerr << "Can't find file " << argv[1] << endl;
		close(source);
		close(target);
		return 1;
	}
	
	if (!target || target < 0)
	{
		cerr << "Can't find file " << argv[2] << endl;
		close(source);
		close(target);
		return 1;
	}
	
	int *buffer[SIZE];
	int bytes = read(source, buffer, size);
	
	if (bytes != write(dest, buffer, bytes))
	{
		cerr << "Unable to write data to file " << argv[2] << endl;
		close(source);
		close(target);
		return 1;
	}
	
	cout << "File successfully copied to " << argv[2] << endl;
	close(source);
	close(target);
	return 0;
}
