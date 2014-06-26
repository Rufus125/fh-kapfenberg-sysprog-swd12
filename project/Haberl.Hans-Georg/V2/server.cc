#include "communication.h"
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

int createListener(int port);
int forkConnection(int main_server_socket, char* ip, int port);
int newConnection(int initialSocket, char* ip, int port);

static int main_port = 8888;

static Score[NUM_SCORES];


int main(int argc, char **argv) {
    //start listening for clients
    int listener_socket = createListener(8888);
    if(listener_socket < 0) {
        return 0;
    }

    while(1) {
        cout << "wainting for incoming connections..." << endl;
        int size = sizeof(struct sockaddr_in);
        struct sockaddr_in client;
        int new_client_socket = accept(listener_socket, (struct sockaddr*) &client, (socklen_t*) &size);
        if (new_client_socket < 0) {
            cerr << "client connection failed" << strerror(errno) << endl;
            continue;
        }
        
        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        int pid = fork();

        if(forkConnection(new_client_socket, client_ip, client_port) < 0) {
            continue;
        }

    }



}

int initScoreCache() {
    //todo: read from file
}

void doCommunicate(int client_socket) {
   int command = retrieveCommand(client_socket); 
   switch(command) {

   }
}

int forkConnection(int initial_socket, char* ip, int port) {
    int client_socket = newConnection(initial_socket, ip, port);
    if(client_socket < 0) return -1;


    int pid = fork();
    if(pid < 0) {
        cerr << ip << ":" << port << 
                ": could not start a new communication process: " 
                << strerror(errno) << endl;
    } else if(pid == 0) {
        int pid_secure = fork();
        if(pid_secure < 0) {
            cerr << ip << ":" << port << 
                    ": could not start a new communication process: " 
                    << strerror(errno) << endl;
        } else if(pid_secure == 0) {
            doCommunicate(client_socket);
            exit(0);
        } else {
            int status = 0;
            sleep(MAX_TIMEOUT_S);
            waitpid(pid_secure, &status, 0);
            if(!WIFEXITED(status)) {
                cerr << ip << ":" << port << 
                        ": communication taking too long, killing communication process." << endl;
                kill(pid_secure,SIGKILL);
            }
            exit(0);
        }
    }
}

int newConnection(int initial_socket, char* ip, int port) {
    int client_specific_server_socket = createListener(0);

    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if(getsockname(client_specific_server_socket, (struct sockaddr *) &sin, &len) < 0) {
        cerr << ip << ":" << port << 
                ": could not retrieve new socket port:" 
                << strerror(errno) << endl;
        close(client_specific_server_socket);
        return -1;
    }

    char buffer[PORT_LEN] = "";
    sprintf(buffer, PORT_STENCIL, sin.sin_port);
    if(send(initial_socket, buffer, sizeof(buffer), 0) < 0) {
        cerr << ip << ":" << port << 
                ": could not send client specific port: " << strerror(errno) << endl;
        close(client_specific_server_socket);
        return -1;
    }

    if(retrieveCommand(initial_socket) < 0) {
        cerr << ip << ":" << port << ": " <<
                "could not aquire acknowledge for new port" << endl;
        return -1;
    }

    return client_specific_server_socket;
}

int createListener(int port) {
    cout << "starting listener port" << endl;

    int main_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(main_server_socket < 0) {
        cerr << "could not create socket: " << strerror(errno) << endl;
        return -1;
    }

    int reuse = 1;
    if(setsockopt(main_server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        cerr << "could not make socket reusable: " << strerror(errno) << endl;
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(main_server_socket,(struct sockaddr*) &server, sizeof(server)) < 0) {
        cerr << "could not bind socket: " << strerror(errno) << endl;
        return -1;
    }

    if(listen(main_server_socket, 3) < 0) {
        cerr << "coult not start listening on port: " << strerror(errno) << endl;
        return -1;
    }
    
    cout << "listener port started" << endl;

    return main_server_socket;
}

//int writeScore(int socket, Score score);
//int writeScores(int socket, Score (&scores)[NUM_SCORES]);
///int retrieveScores(int socket, Score (&scores)[NUM_SCORES]);
//int writeCommand(int socket, Command command);
//int retrieveCommand(int socket);
