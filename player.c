#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Exit status number */
#define EXIT_USAGE 1
#define EXIT_PNUM 2
#define EXIT_BAD_ID 3
#define EXIT_LOSS 4
#define EXIT_BAD_MSG 5

/**
 * Exit status for player
 * All messages to be printed to stderr
 * @param int condition
 */

void exit_status(int condition){
	switch(condition){
		case EXIT_USAGE:
			fprintf(stderr, "Usage: player number_of_players myid\n");
			exit(EXIT_USAGE);
		case EXIT_PNUM:
			fprintf(stderr, "Invalid player count\n");
			exit(EXIT_PNUM);
		case EXIT_BAD_ID:
			fprintf(stderr, "Invalid player ID\n");
			exit(EXIT_BAD_ID);
		case EXIT_LOSS:
			fprintf(stderr, "Unexpected loss of hub\n");
			exit(EXIT_LOSS);
		case EXIT_BAD_MSG:
			fprintf(stderr, "Bad message from hub\n");
			exit(EXIT_BAD_MSG);
		default:
			break;
	}
}


int main(int argc, char const *argv[])
{
	int playerNum = atoi(argv[1]);
	if(argc != 3){
		exit_status(EXIT_USAGE);
	}else if(playerNum < 2 || playerNum > 4){
		exit_status(EXIT_PNUM);
	}

	printf("%s\n", argv[2]);
	return 0;
}