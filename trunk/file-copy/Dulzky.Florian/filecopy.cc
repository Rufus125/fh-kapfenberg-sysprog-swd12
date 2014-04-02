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
        cerr << "Nur 2 Argumente möglich" << endl;
        return EXIT_FAILURE;
    }
    if (argc > 2) {
        source = argv[1];
        dest = argv[2];
    }else if(argc > 1){
        source = argv[1];
        cout << "Bitte Destination eingeben:" << endl;
        cin >> dest;
    }
    else {
        cout << "Bitte Source eingeben:" << endl;
        cin >> source;
        cout << "Bitte Destination eingeben:" << endl;
        cin >> dest;
    }
    
    cout << "Kopiere File von '" << source << "' nach '" << dest << "'" << endl;
    
    int fileSrc = open(source.c_str(), O_RDONLY);
    if(fileSrc < 0){
        cerr << "File nicht gefunden" << endl;
        return EXIT_FAILURE;
    }
    
    int fileDest = open(dest.c_str(), O_WRONLY);
    if(fileDest < 0){
        cerr << "Destination nicht gefunen" << endl;
        close(fileSrc);
        return EXIT_FAILURE;
    }
    
    char buffer[READ_BUFFER_SIZE];
    
    ssize_t bytes = 0;
    
    while ((bytes = read(fileSrc, buffer, READ_BUFFER_SIZE)))
    {
        if (bytes < 0)
        {
            cerr << "Fehler beim lesen des Files" << endl;
            return EXIT_FAILURE;
        }
        
        if (write(fileDest, buffer, bytes) < 0)
        {
            cerr << "Fehler beim schreiben des Files" << endl;
            return EXIT_FAILURE;
        }
    }
    
    close(fileSrc);
    close(fileDest);
    
    return 0;
}
