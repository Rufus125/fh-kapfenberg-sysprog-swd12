#include "communication.h"

using namespace std;

int writeScore(int socket, Score score) {
    char buffer[SCORE_LEN] = "";
    sprintf(buffer, SCORE_STENCIL,
            score.name[0], 
            score.name[1], 
            score.name[2], 
            score.points);
    if(send(socket, buffer, sizeof(buffer), 0) < 0) {
        cerr << "could not send scores" << strerror(errno) << endl;
        return -1;
    }
}

int writeScores(int socket, Score (&scores)[NUM_SCORES]) {
    char buffer[SCORE_LEN*NUM_SCORES] = "";
    for(int i=0; i<NUM_SCORES; i++) {
        sprintf(buffer+i*SCORE_LEN, SCORE_STENCIL, 
                scores[i].name[0], 
                scores[i].name[1], 
                scores[i].name[2], 
                scores[i].points);
    }
    if(send(socket, buffer, sizeof(buffer), 0) < 0) {
        cerr << "could not send scores" << strerror(errno) << endl;
        return -1;
    }
}

int retrieveScores(int socket, Score (&scores)[NUM_SCORES]) {
    char buffer[SCORE_LEN*NUM_SCORES] = "";
    if(recv(socket, buffer, SCORE_LEN*NUM_SCORES, 0) < 0) {
        cerr << "could not retrieve scores" << strerror(errno) << endl;
        return -1;
    }
    for(int i=0; i<NUM_SCORES; i++) {
        if(sscanf(buffer+i*SCORE_LEN, SCORE_STENCIL, 
                &scores[i].name[0], 
                &scores[i].name[1], 
                &scores[i].name[2], 
                &scores[i].points) < 0) {
            cerr << "could not parse scores" << strerror(errno) << endl;
            return -1;
        }
        scores[i].name[3] = '\0';
    }
    return 1;
}

int writeCommand(int socket, Command command) {
    char buffer[COMMAND_LEN] = "";
    sprintf(buffer, COMMAND_STENCIL, command);
    if(send(socket, buffer, sizeof(buffer), 0) < 0) {
        cerr << "could not send command" << strerror(errno) << endl;
        return -1;
    }
}

int retrieveCommand(int socket) {
    char buffer[COMMAND_LEN] = "";
    if(recv(socket, buffer, COMMAND_LEN, 0) < 0) {
        cerr << "could not retrieve command" << strerror(errno) << endl;
        return -1;
    }
    int command = ERROR;
    if(sscanf(buffer, COMMAND_STENCIL, &command) < 0) {
        cerr << "could not parse command" << strerror(errno) << endl;
        return -1;
    }
    return command;
}
