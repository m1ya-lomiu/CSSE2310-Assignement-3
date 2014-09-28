#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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




int main(int argc, char const *argv[])
{
	return 0;
}