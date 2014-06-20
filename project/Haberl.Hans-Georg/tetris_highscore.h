#ifndef __TETRIS_HIGHSCORE__
#define __TETRIS_HIGHSCORE__
int uploadScore(int id, char* name, int score);
int printScores();
int checkScore(int score);
int getNewId();

#endif
