/* Kotremba Achim, Windhaber Thomas */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#define BUFFER_SIZE 4096

int main(int argc, char** argv)
{
  if (argc != 3)
  {
     cerr << "You need to define the source and target" << endl;
     return EXIT_FAILURE;
  }

  cout << "source: " << argv[1] << " Target: " << argv[2] << endl;
	
	int source = open(argv[1], O_RDONLY);
  if (!source || source < 0)
	{
		cerr << "Can't find file " << argv[1] << endl;
		close(source);
		return EXIT_FAILURE;
	}
  
  int target = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (target < 0)
	{
		cerr << "Targetfile " << argv[2] << " already exists." << endl;
		close(source);
		close(target);
		return EXIT_FAILURE;
	}
	
	int *buffer[BUFFER_SIZE];
	int bytes = read(source, buffer, BUFFER_SIZE);
	
	if (bytes != write(target, buffer, bytes))
	{
		cerr << "Unable to write data to file " << argv[2] << endl;
		close(source);
		close(target);
		return EXIT_FAILURE;
	}
	
	cout << "File successfully copied to " << argv[2] << endl;
	close(source);
	close(target);
	return EXIT_SUCCESS;
}
