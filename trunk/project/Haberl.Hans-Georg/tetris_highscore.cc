#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<cerrno>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<cstdlib>
using namespace std;
#define ip_port 8880
#define MSG_LEN 40
#define NUM_SCORES 10
#define ip_address "127.0.0.1"
 
struct Score {
    int id;
    char name[4];
    int score;
};

class Client {
    public:
    Score scores[NUM_SCORES];
    Client() {
        memset(scores, 0, sizeof(scores));
    }
    int connect2Server() {
        struct sockaddr_in server;
        cout << "creating socket..." << endl;
        this->socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (this->socket_desc == -1) {
            cerr << "error creating socket: " << strerror(errno) << endl;
            return -1;
        }
         
        server.sin_addr.s_addr = inet_addr(ip_address);
        server.sin_family = AF_INET;
        server.sin_port = htons(ip_port);
 
        cout << "connecting..." << endl;
        if (connect(this->socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
            cerr << "error connecting to server: " << strerror(errno) << endl;
            return -1;
        }
        return 0;
    }
    int retrieveScores() {
        if(this->connect2Server() < 0) {
            return -1;
        }
        char buffer[MSG_LEN] = "getScore";
        if(send(socket_desc , buffer , MSG_LEN, 0) < 0) {
            cerr << "error sending command [getScore]: " << strerror(errno) << endl;
            return -1;
        }
        
        for(int i=0; i < NUM_SCORES; i++) {
            if(recv(socket_desc, buffer, MSG_LEN, 0) < 0) {
                cerr << "could not retrieve scores: " << strerror(errno) << endl;
                return -1;
            }
            if(sscanf(buffer, "id=[%d];name=[%c%c%c];score=[%d]", 
                    &this->scores[i].id, 
                    &this->scores[i].name[0], 
                    &this->scores[i].name[1], 
                    &this->scores[i].name[2], 
                    &this->scores[i].score) < 0) {
                cerr << "parsing scores failed!" << endl;
                return -1;
            }
        }
    }
    ~Client() {
        close(socket_desc);
    }
    int exit() {
        char buffer[MSG_LEN] = "exit";
        if(send(socket_desc , buffer , MSG_LEN, 0) < 0) {
            cerr << "error sending command [exit]: " << strerror(errno) << endl;
            return -1;
        }
    }

    private:
    int socket_desc;


};

int printScores() {
    Client* client = new Client();    
    if(client->retrieveScores() < 0) {
        delete(client);
        return -1;
    }
    if(client->exit() < 0) {
        return -1;
    }
    system("clear");
    cout << "Name   Score" << endl;
    for(int i=0; i<NUM_SCORES; i++) {
        printf("%s   | %06d\n", client->scores[i].name, client->scores[i].score);
    }
    delete(client);
    return 1;
}

