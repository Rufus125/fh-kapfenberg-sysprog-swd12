#include "tetris_highscore.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;

int create_socket() {
    int socket_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(socket_desc == -1) {
        cerr << "error creating socket" << endl;
        return -1;
    }
    return 1;
}


