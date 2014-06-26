#ifndef __COMMUNICATION__
#define __COMMUNICATION__
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cerrno>
#include <string.h>
#include <unistd.h>

#define NUM_SCORES 10

#define SCORE_STENCIL "score:[%c%c%c]=[%06d]"
#define SCORE_LEN 21

#define COMMAND_STENCIL "command=[%d]"
#define COMMAND_LEN 13

#define PORT_STENCIL "port=[%d]"
#define PORT_LEN 15

#define MAX_TIMEOUT_S 10

struct Score {
    char name[4];
    int points;

};

enum Command {
    ERROR,
    ACK,
    SCORE_UPLOAD,
    SCORE_DOWNLOAD
};

int writeScore(int socket, Score score);
int writeScores(int socket, Score (&scores)[NUM_SCORES]);
int retrieveScores(int socket, Score (&scores)[NUM_SCORES]);
int writeCommand(int socket, Command command);
int retrieveCommand(int socket);


#endif
