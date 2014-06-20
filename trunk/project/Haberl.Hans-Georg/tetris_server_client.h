#ifndef __TETRIS_SERVER_CLIENT__
#define __TETRIS_SERVER_CLIENT__
#define ip_port 8880
#define MSG_LEN 40
#define NUM_SCORES 10
#define ip_address "127.0.0.1"
 
struct Score {
    int id;
    char name[4];
    int score;
};

#endif
