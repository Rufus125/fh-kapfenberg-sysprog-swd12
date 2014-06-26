#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cerrno>
#include <string.h>
#include <unistd.h>
#include"tetris_server_client.h"
using namespace std;

static int id = 10;
static Score scores [NUM_SCORES];

int createServerListener();

int main(int argc, char **argv) {
    for(int i=0; i<NUM_SCORES; i++) {
        scores[i].id = i;
        strcpy(scores[i].name, "AAA");
        scores[i].score = 0;
    }
    createServerListener();
}

int createServerListener() {


    int socket_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(socket_desc == -1) {
        cerr << "error creating socket" << endl;
        return -1;
    }
    
    int reuse = 1;
    if(setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        cerr << "error setting socket option: " << strerror(errno) << endl;
    }

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(ip_port);

    if(bind(socket_desc,(struct sockaddr*) &server, sizeof(server)) < 0) {
        cerr << "error binding socket: " << strerror(errno) << endl;
        return -1;
    }

    //max 3 connections
    if(listen(socket_desc, 3) < 0) {
        cerr << strerror(errno) << endl;
    }

    do {
        cout << "waiting for new incoming connections..." << endl;
        int size = sizeof(struct sockaddr_in);
        int new_socket = accept(socket_desc, (struct sockaddr*) &client, (socklen_t*) &size);
        if (new_socket < 0) {
            cerr << strerror(errno) << endl;
        }

        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        cout << "connected to [" << client_ip << "::" << client_port << "], waiting for command..." << endl;
        char buffer[MSG_LEN];
        do {
            if(recv(new_socket, buffer, MSG_LEN, 0) < 0) {
                cerr << "could not retrieve command: " << strerror(errno) << endl;
                break;
            }
            if(strcmp("getScore", buffer) == 0) {
                cout << "sending scores..." << endl; 
                for(int i=0; i<10; i++) {
                    sprintf(buffer, "id=[%d];name=[%s];score=[%d]", scores[i].id, scores[i].name, scores[i].score);
                    cout << "sending: [" << buffer << "]..." << endl;
                    write(new_socket, buffer, MSG_LEN);
                }
                cout << "scores sent..." << endl;
            } else if(strcmp("getNewId", buffer) == 0) {
                cout << "sending new id..." << endl; 
                sprintf(buffer, "newId[%d]", id++);
                write(new_socket, buffer, MSG_LEN);
            } else if(strcmp("uploadScore", buffer) == 0) {
                cout << "receive scores..." << endl;
                if(recv(new_socket, buffer, MSG_LEN, 0) < 0) {
                    cerr << "could not retrieve new score: " << strerror(errno) << endl;
                    break;
                }
                Score newScore = {};
                if(sscanf(buffer, "id=[%d];name=[%c%c%c];score=[%d]", 
                        &newScore.id, 
                        &newScore.name[0], 
                        &newScore.name[1], 
                        &newScore.name[2], 
                        &newScore.score) < 0) {
                    cerr << "parsing scores failed!" << endl;
                    return -1;
                }
                cout << "received score: " << buffer << endl;
                int place = NUM_SCORES;
                for(int i = 0; i < NUM_SCORES; i++) {
                    if(newScore.score >= scores[i].score) {
                        cout << "...which is " << i+1 << " place..." << endl;
                        place = i;
                        break;
                    }
                }
                if(place < NUM_SCORES) {
                    cout << " copy ... " << endl;
                    for(int i = NUM_SCORES-1; i >= place; i--) {
                        memcpy(&scores[i], &scores[i-1], sizeof(Score));
                    }
                    memcpy(&scores[place], &newScore, sizeof(newScore));
                    scores[place].id = newScore.id;
                    strcpy(scores[place].name, newScore.name);
                    scores[place].score = newScore.score;
                }
                break;
            } else if(strcmp("exit", buffer) == 0) {
                cout << "exit command retrieved..." << endl;
                break;
            } else {
                cerr << "invalid command: " << buffer << endl;
                break;
            }
        } while (true);
        close(new_socket);
    } while (1);
    close(socket_desc);
}

