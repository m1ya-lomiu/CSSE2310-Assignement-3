#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Exit status number*/
#define EXIT_USAGE 1
#define EXIT_FILE 2
#define EXIT_READ 3
#define EXIT_START 4
#define EXIT_PQUIT 5
#define EXIT_INVALID_MSG 6
#define EXIT_SIG_CAUGHT 7

/**
 * Exit status for hub
 * All messages to be printed to stderr
 * @param int condition
 */
 void exit_status(int condition){
 	switch(condition){
 		case EXIT_USAGE:
 			fprintf(stderr, "Usage: hub deckfile prog1 prog2 [prog3 [prog4]]\n");
 			exit(EXIT_USAGE);
 		case EXIT_FILE:
 			fprintf(stderr, "Unable to access deckfile\n");
 			exit(EXIT_FILE);
 		case EXIT_READ:
 			fprintf(stderr, "Error reading deck\n");
 			exit(EXIT_READ);
 		case EXIT_START:
 			fprintf(stderr, "Enable to start subprocess");
 			exit(EXIT_START);
 		case EXIT_PQUIT:
 			fprintf(stderr, "Player quit\n");
 			exit(EXIT_PQUIT);
 		case EXIT_INVALID_MSG:
 			fprintf(stderr, "Invalid message received from player\n");
 			exit(EXIT_INVALID_MSG);
 		case EXIT_SIG_CAUGHT:
 			fprintf(stderr, "SIGINT caught\n");
 			exit(EXIT_SIG_CAUGHT);
 		default:
 			break;
 	}
 }

/**
 * Read deck file
 * @param file* filename
 * @return int numOfRows
 */
int read_file(char *filename, char **deckContent){
 	FILE *fp;
	char row[1000];
	int numOfRows = 0;
  
	fp = fopen(filename, "r");
	if(fp == NULL){
		exit_status(EXIT_FILE);
  	}
    
  	while(fgets(row, sizeof(row), fp)!= NULL) {
    	strcpy(*deckContent, row);
    	deckContent++;
    	numOfRows++;
  	}
    
  	fclose(fp);
  	return numOfRows;
}


int main(int argc, char *argv[])
{
	/* Store the content of the deck file */
	char **deckContent;
	deckContent = malloc(1000 * sizeof(char*));
	for(int i=0; i<1000; i++){
   		deckContent[i] = malloc(1000 * sizeof(char));
  	}

  	int numOfRounds;
  	/* Read from the deck file */
  	numOfRounds = read_file(argv[1], deckContent);

	/* Calculate the number of players */
	int numOfPlayer = argc - 2;
	char strNumOfPlayer[15];
	sprintf(strNumOfPlayer, "%d", numOfPlayer);

	pid_t pid[numOfPlayer];
	int child_status;

	/* Start running the players' programs */
	for(int i = 0; i < numOfPlayer; i++){
		int sizeOfArg = strlen(argv[i+1]);
		char *playerName;
		playerName = malloc(sizeOfArg);
		playerName[0]='\0';
		strcat(playerName, argv[i+2]);

		if((pid[i] = fork()) == 0){
			/*Child*/
			execlp("./player", "./player", strNumOfPlayer, playerName, NULL);					
		}else{
			/*Parent*/
			wait(&child_status);
		}
	}

	/* Free the deckContent*/
	for(int i=0; i<1000; i++){
    	free(deckContent[i]);
  	}
  	free(deckContent);
	
}