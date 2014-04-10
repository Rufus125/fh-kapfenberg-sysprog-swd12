#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using namespace std;

const char msg[] = "hallo du!\n";

static void write_all(int fd, const char *data, size_t len)
{
    while (len != 0) {
        ssize_t written = write(fd, data, len);
        if (written == -1) {
            perror("write");
            abort();
        }
        data += written;
        len -= written;
    }
}

int main()
{
    int pipe_fd[2];

    int err = pipe(pipe_fd);
    if (err == -1) {
        perror("pipe");
        abort();
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        abort();
    }
    else if (pid == 0) {
        // child. close parent's end.
        close(pipe_fd[0]);
        for (int i=0; i<30; i++) {
            write_all(pipe_fd[1], msg, sizeof(msg));
            sleep(2);
        }
        // done; close pipe so parent can realize we are done
        close(pipe_fd[1]);
        // important: do not escape into parent code        
        exit(0);
    }
    else {
        // parent. close child's end.
        close(pipe_fd[1]);
        for (;;) {
            char readbuf[3];
            ssize_t nread = read(pipe_fd[0], readbuf, sizeof(readbuf));
            if (nread > 0) {
                cout << nread << ':';
                cout.write(readbuf, nread);
                cout << endl;
            }
            else if (nread == 0) {
                cerr << "\n<<< END OF INPUT" << endl;
                break;
            }
            else {
                perror("read");
                abort();
            }
        }
    }

    return 0;
}
