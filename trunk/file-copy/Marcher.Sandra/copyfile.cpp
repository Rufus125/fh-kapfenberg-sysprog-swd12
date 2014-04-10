#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define count 64

int main (int argc,char** argv)
{
        if (argc != 3) {
                fprintf(stderr, "Anzahl der Argumente passt nicht");
                return 1;
        }

    // oeffnet File
    int file = open(argv[1], O_RDONLY); 
        if (file == -1){
                perror("File konnte nicht geöffnet werden");
                        return 1;
        }

    // oeffnet Outputfile und setzt Zugriffsrechte
    int outputfile = open(argv[2],O_WRONLY | O_CREAT | O_EXCL, S_IRWXU,  S_IRWXG, S_IROTH); 
        if (outputfile == -1){
                perror("Ziel-File konnte nicht geöffnet werden");
                        return 1;
        }

    //lesen des Files 
    char buf[count];
    while (ssize_t bytes = read(file, buf, count)){
        if (bytes == -1){
            perror("File konnte nicht gelesen werden");
            return 1;
        }
        
        if (write(outputfile, buf, bytes) == -1){
            perror("File konnte nicht geschrieben werden");
            return 1;  
        }
    }

return 0;
}
