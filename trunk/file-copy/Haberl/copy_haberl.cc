/* Hans-Georg Haberl */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define RD_SIZE 4096

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "please enter source & target file" << endl;
        return EXIT_SUCCESS;
    }

    int srcFd = open(argv[1], O_RDONLY);
    if (srcFd < 0) {
        cerr << "error while retrieving the source file descriptor" << endl;
        return EXIT_FAILURE;
    }

    int targetFd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (targetFd < 0) {
        cerr << "error while retrieving the target file descriptor" << endl;
        close(srcFd);
        return EXIT_FAILURE;
    }

    char buf[RD_SIZE] = "";

    ssize_t bytes = 0;

    while ((bytes = read(srcFd, buf, RD_SIZE))) {
        if (bytes < 0) {
                cerr << "reading from source file failed" << endl;
                close(srcFd);
                close(targetFd);
                return EXIT_FAILURE;
        }

        if (write(targetFd, buf, bytes) < 0) {
                cerr << "writing to target file failed" << endl;
                close(srcFd);
                close(targetFd);
                return EXIT_FAILURE;
        }
    }

    close(srcFd);
    close(targetFd);

    return EXIT_SUCCESS;
}
