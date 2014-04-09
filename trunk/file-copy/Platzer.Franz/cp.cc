/* Franz Platzer
 * 28.3.2014
 * SWD 12
 * My personal "CP" version
 */

// simple out- and input
#include <iostream>
#include <stdlib.h>

// close/read/write
#include <unistd.h>

// open
#include <fcntl.h>

// error number output
#include <errno.h>
#include <string.h>

// file infos
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int checkArguments(int argc, char** argv);
void outputOpenFileError(int errorNr);
int getFileMode(char* path);
int copy(char* source, char* target, int fileMode);

const int ERROR = 1;
const int SUCCESS = 0;

int main(int argc, char** argv)
{
	if(checkArguments(argc, argv) == ERROR)
	{
		return ERROR;
	}
	
	int fileMode = getFileMode(argv[1]);

	if(fileMode == ERROR){
		return ERROR;	
	}

	return copy(argv[1], argv[2], fileMode);
}

int getFileMode(char* path)
{
	struct stat* fileInfo = (struct stat*) malloc(sizeof(struct stat));
	int statReturn = stat(path, fileInfo);

	if(statReturn != 0){
		cerr << "Couldn't read file info for source file!" << endl;	
		free(fileInfo);
		return ERROR;
	}

	int fileMode = 0666; // rw-rw-rw-
	fileMode = fileInfo->st_mode;
	free(fileInfo);

	return fileMode;
}

int copy(char* source, char* target, int fileMode)
{
	errno = 0;
	int sourceHandle = open(source, O_RDONLY);

	if(sourceHandle < 0){
		outputOpenFileError(errno);
		close(sourceHandle);
		return ERROR;
	}

	int destHandle = open(target, O_WRONLY | O_EXCL | O_CREAT, fileMode);
	
	if(destHandle < 0){
		outputOpenFileError(errno);
		close(sourceHandle);
		close(destHandle);
		return ERROR;
	}

	int result = SUCCESS;
	
	int bufferSize = 2048;
	char buffer[bufferSize];

	int readResult = 0;	

	while((readResult = read(sourceHandle, buffer, bufferSize)) != 0) // 0 = EOF
	{
		if(read < 0){
			result = ERROR;
			cerr << "Read failed!" << endl;
			break;
		}

		if(write(destHandle, buffer, readResult) <= 0){
			result = ERROR;
			cerr << "Write failed!" << endl;
			break;
		}
	}

	close(sourceHandle);
	close(destHandle);

	return result;
}

int checkArguments(int argc, char** argv)
{
	if(argc != 3){
		cerr << "Argument count is wrong!\nUsage: cp <source> <destination>" << endl;
		return ERROR;
	}
	
	if(!argv[1]){
		cerr << "The source is not valid!" << endl;
		return ERROR;
	}

	if(!argv[2]){
		cerr << "The destination is not valid!" << endl;
		return ERROR;
	}

	return SUCCESS;
}

void outputOpenFileError(int errorNr)
{
	cerr << "failed with error: " << strerror(errorNr) << endl;
}


