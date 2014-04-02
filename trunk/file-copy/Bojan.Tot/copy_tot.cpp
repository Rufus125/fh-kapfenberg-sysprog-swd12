#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>

#define BUF_SIZ 4096

int copyFile(int source, int dest, ssize_t infile, ssize_t outfile, char buffer[]);

int main(int argc, char** argv) {

	char* inpath = argv[1];
	char* outpath = argv[2];

	if (argc < 3) {
		std::cerr << "Please enter the source and the destination file."
				<< std::endl;
		return (EINVAL);
	}

	if (argc > 3) {
		std::cerr << "Two arguments required." << std::endl;
		return (EINVAL);
	}

	int fo = open(inpath, O_RDONLY);

	if (!fo) {
		std::cerr << "Error opening file!" << std::endl;
		return (ENOENT);
	}

	int fw = open(outpath, O_WRONLY | O_CREAT | O_TRUNC);

	if(!fw){
		std::cerr << "Error creating output file!" << std::endl;
		return (EIO);
	}

	char buffer[BUF_SIZ];
	ssize_t infile = read(fo, buffer, BUF_SIZ);
	ssize_t outfile = 0;
	copyFile(fo, fw, infile, outfile, buffer);

	close(fo);
	close(fw);

	return 0;
}

int copyFile(int source, int dest, ssize_t infile, ssize_t outfile, char buffer[]){

	while (infile > 0){

		outfile = write(dest, buffer, infile);
		if (outfile == -1) {
			std::cerr << "Could not write file" << std::endl;
			return (EIO);
		}
		infile = read(source, buffer, BUF_SIZ);
		if (infile == -1) {
			std::cerr << "Could not read file" << std::endl;
			return (EIO);
		}

	}
	return 0;
}





