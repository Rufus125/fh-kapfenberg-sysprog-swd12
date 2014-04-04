/* Michael Mayer | SWD12 */
#include <iostream>
#include <cerrno>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#define E_INVARGS 1
#define E_FILE_NOT_FOUND 2
#define E_WRITE_ERROR 3
#define E_CLOSE_FILE 4

#define BUF_SIZE 4096

int copy_files(const char* src, const char* dest);

int main(int argc, char** argv)
{
    if(argc < 3 || argc > 3)
    {
        cerr << "invalid arguments. usage <src> <dest>" << endl;
        return E_INVARGS;
    }
    copy_files(argv[1], argv[2]);
    return 0;
}


int copy_files(const char* src, const char* dest)
{
    // open source file in read mode.
    int fdsrc = open(src, O_RDONLY);
    if(fdsrc < 0)
    {
        cerr << "file not found: " << src << endl;
        return E_FILE_NOT_FOUND;
    }
    // create destination file, but only if it not exists.
    // let open(..) set the following permission (0666 & ~umask)
    int fddest = open(dest, O_CREAT | O_WRONLY | O_EXCL, 0666);
    if(fddest < 0)
    {
        cerr << "file exists" << endl;
        return EEXIST;
    }
    char buffer[BUF_SIZE];
    int read_bytes = 0;
    while((read_bytes = read(fdsrc, buffer, BUF_SIZE)) > 0)
    {
        if(write(fddest, buffer, read_bytes) < 0)
        {
            // error occured while writing to file.
            cerr << "write to destination file failed" << endl;
            return E_WRITE_ERROR;
        }
    }
    if(close(fdsrc) < 0 || close(fddest) < 0)
    {
        return E_CLOSE_FILE;
    }
    return 0;
}
