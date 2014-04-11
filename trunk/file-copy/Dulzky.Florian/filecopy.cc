#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#define READ_BUFFER_SIZE 4096

int main(int argc, char** argv)
{
    string source;
    string dest;
    if(argc > 3){
	perror("Nur 2 Argumente möglich: ");
        return EXIT_FAILURE;
    }
    if (argc > 2) {
        source = argv[1];
        dest = argv[2];
    }else if(argc > 1){
        source = argv[1];
        cerr << "Bitte Destination eingeben:" << endl;
        cin >> dest;
    }
    else {
	cerr << "Bitte Source eingeben:" << endl;
        cin >> source;
	cerr << "Bitte Destination eingeben:" << endl;
        cin >> dest;
    }
    
    cerr << "Kopiere File von '" << source << "' nach '" << dest << "'" << endl;
    
    int fileSrc = open(source.c_str(), O_RDONLY);
    if(fileSrc < 0){
	perror("file nicht gefunden: ");
        return EXIT_FAILURE;
    }
    
    int fileDest = open(dest.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if(fileDest < 0){
	perror("Destination kann nicht erstellt werden: ");
        close(fileSrc);
        return EXIT_FAILURE;
    }
    
    char buffer[READ_BUFFER_SIZE];
    
    ssize_t bytes = 0;
    
    while ((bytes = read(fileSrc, buffer, READ_BUFFER_SIZE)))
    {
        if (bytes < 0)
        {
	    perror("Fehler beim lesen des Files: ");
            return EXIT_FAILURE;
        }
        
        if (write(fileDest, buffer, bytes) < 0)
        {
	    perror("Fehler beim schreiben des Files: ");
            return EXIT_FAILURE;
        }
    }
    
    close(fileSrc);
    close(fileDest);
    
    return 0;
}
