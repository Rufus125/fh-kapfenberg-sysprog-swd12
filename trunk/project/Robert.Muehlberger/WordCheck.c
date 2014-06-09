/*----------------------------------------------------*/
/* WordCheck.c                                090614  */
/* Robert Muehlberger                   			  */
/*                                                    */
/* a simple console game                              */
/* this file was created by Prof. Gerhard Jahn        */
/* basic file for socket lession					  */	
/*----------------------------------------------------*/

#include<errno.h>
#include<syslog.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>

#define WORDLEN 	  	30   /* needed for the buffer size */

#define INCOMPLETE 		1    /* game is still running */
#define WON 		    	2    /* player has won! */
#define LOST 			    3    /* player has lost! */


//int main(){
//	 /* starts the server process locally (no network) */
//	 /* 0 = stdin; 1 = stdout */
//   ServerProcess(0,1);   
//} 

/* ServerProcess plays Hangman with a single player */
/* IN: stream to read input from                    */
/* OUT: stream to stream to write output to         */

void ServerProcess (int in,  int out) {
	int	  max_lives=10;	       /* number of guesses we offer */
	char  *words []= { 		     /* the words to be guessed */
			"home",
			"ubuntu",
			"zombie",
			"daemon"
}; /* ServerProcess */

 	char  part_word [WORDLEN],        /* contains the guessed part */
 		  *whole_word,                  /* contains the whole word */
 		  guess_word[WORDLEN],          /* contains the word to be guessed */          
 		  hostname[WORDLEN],            /* hostname (not used...) */
 		  outbuff[WORDLEN];             /* output buffer */
 	
	int	 lives,                       /* number of initial lives */
     	 word_len,                    /* length of the word to be guessed */
     	 game_status = INCOMPLETE,    /* initial status of the game */
     	 hits,                        /* number of hits */
     	 i;
 	time_t  timer;
    struct tm *t;

	/* initialize  */
 	lives = max_lives;

	/* pick up a random word */
 	time (&timer);
 	t = (struct tm *) malloc (sizeof (struct tm));
 	t = localtime (&timer);
 	whole_word = words [
	  (t->tm_sec + rand()) %
	  (sizeof (words) / sizeof (char*))
	  ];
 	word_len = strlen (whole_word);
 	syslog (LOG_USER|LOG_INFO,
  		"word server chooses word %s ",whole_word);
 
	/* initialize empty word */
 	for (i=0; i<word_len; i++)
		part_word [i]='-';
 	part_word [i]= '\0';

	/* output empty word */
 	sprintf (outbuff, "%s  lives:%d \n", part_word, lives);
 	write (out, outbuff, strlen (outbuff));

	/* do the game */
 	while (game_status == INCOMPLETE) {
  		while (read (in, guess_word, WORDLEN) < 0) {
			/* restart if interrupted by signal ??  */
			if (errno != EINTR) 
				perror ("reading players guess");
				exit(1);
   			printf("re-starting the read\n");
  		}

		/* check for hits */
  		hits = 0;
  		for (i=0; i<word_len; i++) {
			if (guess_word[0] == whole_word [i]) {
    			hits=1;
    			part_word[i] = whole_word[i];
   			} /* if */
  		} /* for */

		/* check for end of game */
  		if (!hits) {
			  lives--;
			if (lives == 0) {
				game_status = LOST;
			} /* game is over */
			
		} /* lost one life */
  		if (strcmp (part_word, whole_word) == 0) {
			  /* he did it */
			  game_status = WON;
   			sprintf (outbuff, "You won!\n");
   			write (out, outbuff, strlen(outbuff));
   			return;
  		} /* if */ 
			
			/* game over */
			else if (lives == 0) {
   			game_status = LOST;
   			strcpy (part_word, whole_word);
  		} /* else */
			
		/* show word */
  		sprintf (outbuff,  "%s  lives: %d \n",  part_word,lives);
  		write (out, outbuff, strlen (outbuff));
  		if (game_status == LOST) {
   			sprintf (outbuff, "\nGame over.\n");
   			write (out, outbuff, strlen (outbuff));
  		} /* he looses */
 	} /* game is incomplete */
} /* ServerProcess */
