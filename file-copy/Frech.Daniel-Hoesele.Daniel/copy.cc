// Daniel Hösele - 1210418031 - SWD12

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3) {
        cerr << "Program need exactly 2 arguments" << endl;
        return 1;
    }
    
    cout << "Source: " << argv[1] << endl;
    cout << "Destination: " << argv[2] << endl;
    
    int c;
    FILE *source, *dest;
    
    source = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");
    
    if (source == NULL || !source) {
		cerr << "No such file: " << argv[1] << endl;
		return 0;
	}
	else if (dest == NULL || !dest) {
		cerr << "No such file: " << argv[2] << endl;
		return 0;
	}
	else {
		while ((c=getc(source))!=EOF)
			putc(c,dest);
			
		fclose(source);
		fclose(dest);
	}
	cout << "Data successfully written to: " << argv[2] << endl;
    return 0;
}
