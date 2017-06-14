#ifndef STREE_H
#define STREE_H

#include <stdlib.h>
#include <stdbool.h>
#include "engine.h"
//State space search header

typedef struct
{
	char mov;
	signed char util;
} ret; //simple struct for indicating the utility of a move

ret search(board b, char cpu, char just, char move, char nxt, bool dmax); //state space search. player 'just' moved in cell 'move' of b, but b doesn't reflect this. player nxt's turn is next. dmax indicates whether to do min or max
ret cpu_move(board b, char cpu); //pick the cpu's move. entry point for state space search

#endif
