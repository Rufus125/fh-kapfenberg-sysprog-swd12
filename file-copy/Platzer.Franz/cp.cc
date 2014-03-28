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
int setFileInfos(char* path);
char* getFilecontent(char* path);
int writeFilecontent(char* target, char* content);

const int ERROR = 1;
const int SUCCESS = 0;

int fileSize = 0;
int fileMode = 0664;

int main(int argc, char** argv)
{
	if(checkArguments(argc, argv) == ERROR)
	{
		return ERROR;
	}
	
	if(setFileInfos(argv[1]) == ERROR){
		return ERROR;	
	}

	char* filecontent = getFilecontent(argv[1]);

	if(!filecontent){
		return ERROR;
	}

	int writeResult = writeFilecontent(argv[2], filecontent);
	free(filecontent);	

	if(writeResult == ERROR){
		return ERROR;	
	}

	cout << "Successfully copied!" << endl;

    return SUCCESS;
}


int setFileInfos(char* path)
{
	struct stat* fileInfo = (struct stat*) malloc(sizeof(struct stat));
	int statReturn = stat(path, fileInfo);

	if(statReturn != 0){
		cerr << "Couldn't read file info for source file!" << endl;	
		free(fileInfo);
		return ERROR;
	}

	fileSize = fileInfo->st_size;
	fileMode = fileInfo->st_mode;
	free(fileInfo);

	return SUCCESS;
}

char* getFilecontent(char* path)
{
	errno = 0;
	int sourceHandle = open(path, O_RDONLY);

	if(sourceHandle == -1){
		outputOpenFileError(errno);
		close(sourceHandle);
		return NULL;
	}

	char* sourceFileContent = (char*) malloc(sizeof(char)*fileSize);
	
	int readResult = read(sourceHandle, sourceFileContent, fileSize);
	if(readResult < 0)
	{
		cerr << "read file failed with: " << strerror(readResult) << endl;
		free(sourceFileContent);
		close(sourceHandle);
		return NULL;
	}

	close(sourceHandle);
	return sourceFileContent;
}

int writeFilecontent(char* target, char* content)
{
	int destHandle = open(target, O_WRONLY | O_TRUNC | O_CREAT, fileMode);
	
	if(destHandle < 0){
		outputOpenFileError(errno);
		close(destHandle);
		return ERROR;
	}

	int writeResult = write(destHandle, content, fileSize);
	if(writeResult < 0){
		cerr << "write file failed with: " << strerror(writeResult) << endl;
		close(destHandle);
		return ERROR;	
	}

	close(destHandle);
	return SUCCESS;
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

	cout << "Source: " << argv[1] << "\nDestination: " << argv[2] << endl;
	return SUCCESS;
}

void outputOpenFileError(int errorNr)
{
	cerr << "open() failed with error: " << strerror(errorNr) << endl;
}


