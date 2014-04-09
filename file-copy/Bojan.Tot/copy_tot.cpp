/*
 * Tot Bojan
 * Date: 08.04.14
 * Descr: cp-clone
 */

#include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>

#define BUF_SIZ 4096

int copyFile(int source, int dest, ssize_t infile, ssize_t outfile,
		char buffer[]);

int main(int argc, char** argv) {

	char* inpath = argv[1];
	char* outpath = argv[2];
	int fw;
	int fo;
	int permission = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	char buffer[BUF_SIZ];
	ssize_t infile;
	ssize_t outfile = 0;

	if (argc < 3) {
		perror("Please enter the source and the destination file.");
		exit(EXIT_FAILURE);
	}

	if (argc > 3) {
		perror("Two arguments required.");
		exit(EXIT_FAILURE);
	}

	if ((fo = open(inpath, O_RDONLY)) < 0) {
		perror("Error opening file!");
		close(fo);
		exit(EXIT_FAILURE);
	}

	if ((fw = open(outpath, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, permission))
			< 0) {

		if (errno == EEXIST) {
			perror("Error ");
		} else {
			perror("Error creating output file!");
		}
		close(fw);
		exit(EXIT_FAILURE);
	}

	infile = read(fo, buffer, BUF_SIZ);
	copyFile(fo, fw, infile, outfile, buffer);

	close(fo);
	close(fw);

	return 0;
}

int copyFile(int source, int dest, ssize_t infile, ssize_t outfile,
		char buffer[]) {

	while (infile > 0) {

		infile = read(source, buffer, BUF_SIZ);
		if (infile == -1) {
			perror("Could not read file");
			exit(EXIT_FAILURE);
		}

		outfile = write(dest, buffer, infile);
		if (outfile == -1) {
			perror("Could not write file");
			exit(EXIT_FAILURE);
		}

	}
	return 0;
}

