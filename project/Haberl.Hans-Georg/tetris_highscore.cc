#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<cerrno>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<cstdlib>
#include"tetris_server_client.h"
using namespace std;

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
    int getNewId() {
        if(this->connect2Server() < 0) {
            return -1;
        }
        char buffer[MSG_LEN] = "getNewId";
        if(send(this->socket_desc , buffer , MSG_LEN, 0) < 0) {
            cerr << "error sending command [getNewId]: " << strerror(errno) << endl;
            return -1;
        }
        if(recv(this->socket_desc, buffer, MSG_LEN, 0) < 0) {
            cerr << "could not retrieve scores: " << strerror(errno) << endl;
            return -1;
        }
        int newId = 0;
        if(sscanf(buffer, "newId[%d]", &newId) < 0 || newId <= 0) {
            cerr << "parsing new id failed" << endl;
            return -1;
        }
        return newId;

    }
    int sendScore(int id, char* name, int score) {
         cout<<"STAAAART"<<endl;
        if(this->connect2Server() < 0) {
            return -1;
        }
        char buffer[MSG_LEN] = "uploadScore";
        write(this->socket_desc , buffer , MSG_LEN);
        sprintf(buffer, "id=[%d];name=[%s];score=[%d]", id, name, score);
        if(send(this->socket_desc, buffer, MSG_LEN, 0) < 0) {
            cerr << "error sending score: " << strerror(errno) << endl;
            return -1;
        }
        if(recv(this->socket_desc, buffer, MSG_LEN, 0)) {
            cerr << "could not retrieve acknowledge" << endl;
            return -1;
        }
        if(strcmp(buffer, "OK") != 0) {
            cerr << "could not parse acknowledge" << endl;
            return -1;
        }
        return 1;
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
    int checkScore(int score) {
        if(this->retrieveScores() < 0) {
            return -1;
        }
        int newHighscore = 0;
        for(int i = NUM_SCORES; i >= 0 && scores[i].score <= score; i--) {
            newHighscore = i;
        }
        return newHighscore + 1;
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

int checkScore(int score) {
    Client* client = new Client();    
    int newHighScore = client->checkScore(score);
    if(newHighScore < 0) {
        delete(client);
        return -1;
    }
    if(client->exit() < 0) {
        delete(client);
        return -1;
    }
    delete(client);
    return newHighScore;
}

int printScores() {
    Client* client = new Client();    
    if(client->retrieveScores() < 0) {
        delete(client);
        return -1;
    }
    if(client->exit() < 0) {
        delete(client);
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


int getNewId() {
    Client* client = new Client();    
    int newId = client->getNewId();
    if(newId < 0) {
        delete(client);
        return -1;
    }
    if(client->exit() < 0) {
        delete(client);
        return -1;
    }
    delete(client);
    return newId;
}

int uploadScore(int id, char* name, int score) {
    Client* client = new Client();    
    if (client->sendScore(id, name, score) < 0) {
        delete(client);
        return -1;
    }
    if(client->exit() < 0) {
        delete(client);
        return -1;
    }
    delete(client);
    return 1;
}
