/* Fritz Eva - Schuberth Jürgen */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

# define READ_BUFFER_SIZE 50

int main (int argc,char** argv )
{
	if (argc != 3) {

		fprintf(stderr, "Zu wenig Argumente");
		return 0;

	}

	int source = open(argv[1], O_RDONLY); //File Descriptor
	if (source == -1){
		perror("Fehler beim Lesen");
		fprintf(stderr, "Fehlernummer: %d\n",errno);
			close(source);
			return 0;

	}

	int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int target = open(argv[2],O_WRONLY | O_CREAT | O_EXCL, mode);

	if (target == -1){
			perror("Fehler beim Schreiben");
			fprintf(stderr,"Fehlernummer:  %d\n",errno);
				close(source);
				return -1;
	}

	ssize_t bytes = 0;
	ssize_t save = 0;

	char buffer[READ_BUFFER_SIZE];
	do {
	bytes = read(source, buffer, READ_BUFFER_SIZE);

		if (bytes <= 0){
			if (bytes == -1){
				perror("Fehler beim Lesen: ");
				fprintf(stderr, "Fehlernummer:  %d\n",errno);
			}

			break;
		}
	save = write(target, buffer, bytes);
	if (save == -1){
			perror("Fehler beim Lesen");
			fprintf(stderr, "Fehlernummer:  %d\n",errno);
		}
	}

	while (bytes > 0 && save > 0);

	close(source);
	close(target);
   return 0;
}

