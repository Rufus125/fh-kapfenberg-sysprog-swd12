#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cerrno>
#include <string.h>
#include <unistd.h>
using namespace std;
#define ip_port 8880
#define MSG_LEN 40

static int id = 0;

int createServerListener();

int main(int argc, char **argv) {
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
                    sprintf(buffer, "id=[%d];name=[%s];score=[%d]", i, "AAA", 0);
                    cout << "sending: [" << buffer << "]..." << endl;
                    write(new_socket, buffer, MSG_LEN);
                }
                cout << "scores sent..." << endl;
            } else if(strcmp("newScore", buffer) == 0) {
                if(recv(new_socket, buffer, MSG_LEN, 0) < 0) {
                    cerr << "could not retrieve new score!" << endl;
                    break;
                }
                int newId = 0;
                char newName[MSG_LEN] = "";
                int newScore = 0;
                
                if(sscanf(buffer, "id=[%d];name=[%s];score=[%d]", &newId, newName, &newScore) < 0) {
                    cerr << "invalid score recived!" << endl;
                    break;
                }
                cout << "new score: " << newName << ": " << newScore << endl;
                sprintf(buffer, "OK");
                write(new_socket, buffer, MSG_LEN);
                
            } else if(strcmp("exit", buffer) == 0) {
                cout << "exit command retrieved...";
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

