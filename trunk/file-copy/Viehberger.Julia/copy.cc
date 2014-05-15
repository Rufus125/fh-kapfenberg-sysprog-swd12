#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define BUFFER_SIZE 4096


int main(int argc, char** argv){
	
	if (argc != 3) {
		perror("Bitte Source & Destination eingeben");
		return EXIT_FAILURE;
	}
	
		
	int source = open(argv[1], O_RDONLY);
	int destination = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR);
	char buffer[BUFFER_SIZE];
	ssize_t lesen = 0;
	ssize_t schreiben = 0;
	
	
	
	
	if (source <0) {
		perror("Error beim File öffnen");
		return EXIT_FAILURE;
		
		
		};
		
	if (destination <0) {
		perror("Error!");
		close(source);
		return EXIT_FAILURE;
				
		};
		
		
		while ((lesen = read(source, buffer, BUFFER_SIZE))) {
		
			
			if (lesen == -1) {
			perror("Could not read file");
			return (EXIT_FAILURE);
					
			}
			
			schreiben = write(destination, buffer, lesen);
			if (schreiben == -1) {
			perror("Could not write file");
			return (EXIT_FAILURE);
					
			}
			
		}	
	
	
	
	close(source);
	close(destination);
	return 0;
	
	
}
