#ifndef NINE_H
#define NINE_H

//9-board tic-tac-toe

#include <stdbool.h>
#include "engine.h"

typedef struct nflags
{
	flags f[9];
} nflags; //a struct of nine flags for bitflags across all 9 boards

typedef struct nb_t
{
	board bds[9]; //nine boards
	signed char must; //the board the next player must play on. -1 if they may play on any board
	signed char won; //same as board iswon. -1 if tied, 1 if player1, 2 if player2 0 if no winner yet
	nflags nopens; //nflags indicating open cells across all boards
} nb_t;

typedef nb_t *nboard;

nboard init_nboard(nflags p1movs, nflags p2movs); //initialize an nboard with the indicated moves
nboard dup_nboard(nboard n); //duplicates an nboard
void free_nboard(nboard n); //frees n

char getnpos(nboard n, int bd, int pos); //returns the player at pos in board bd. 0=none, 1=player1, 2=player2
void setnpos(nboard n, int bd, int pos, char plr); //places plr's mark on pos on board bd in n, modifies won, bdwon, must, bd's opens and iswon
bool isnvalid(nboard n, int bd, int pos); //returns whether the designated cell in the designated board is empty (i.e., 0)

signed char setnwon(nboard n); //set the won of n and return it. -1 if tie, 1 if player1, 2 if player2, 0 if no winner
nflags setnopens(nboard n); //call setwon on each board in n, returning their results. mostly used to set them all, the return isn't really used

void print_nboard(nboard n); //print the nboard to stderr

#endif
