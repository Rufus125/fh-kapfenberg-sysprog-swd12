/**
 * Program by Robert Muehlberger
 * 
 * Copy one source file to the destination file.
 * Use only systemcalls open/read/write/close
 * Permissions of both file must be the same after copy.
 * If destination file allready exist, send message "File Exist!"
 * 
 * DO NOT USE stdout!
 * 
 */ 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// small buffer size to make sure, that while loop at line 52 
// has something to do...smile
#define BUF_SIZE 10

/** Copy one file to given one 
 * input: argv[1] sourcefile
 * input: argv[2] destinationfile
 * return: 0 if all done very well, otherwise 1
 */
int main(int argc, char* argv[]) {

	int fs,fd;			// Filehandl
	int buf[BUF_SIZE] ; 
	int size ; 			 

	if(argc != 3){
		fprintf(stderr, "Please use: %s sourceFile destinationFile  \n", *argv);
		return EXIT_FAILURE;
	} // if
	

	fs = open(argv[1],O_RDONLY);
	if (fs == 0) {
		fprintf(stderr,"Sorry error source file \n"); 
		return EXIT_FAILURE;
	} // if

	fd = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, 0644);
	/* Some problem occurs */
	if (fd == -1) {  
		fprintf(stderr, "Sorry, error destination file: %s \n", argv[2]); 
		if(errno == EEXIST) {
			fprintf(stderr, "File allready exist!\n"); 
		} // if	
		close(fs);
		return EXIT_FAILURE;
	} // if


	/* Now copy the file from source to destination */ 
	size = read(fs,buf,BUF_SIZE);
	while (size > 0) {
		write(fd,buf,size); 
		size = read(fs,buf,BUF_SIZE);
	} // while

	if (size == -1) {
		fprintf(stderr, "Error on copy! \n");
	} //  if
	
	/* Close all opened handles */ 
	close(fs);
	close(fd);

	
	/* Everything was okay */
	return EXIT_SUCCESS;
} /*main*/
