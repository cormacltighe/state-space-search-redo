#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//Tic-tac-toe game engine

typedef uint16_t flags;

extern const flags const cellflags[9];//flags for inticating a true/false value about each cell in a board
extern const char const cellvals[9];//value of a cell, number of ways that cell can be involved in a win

typedef struct board_t
{
	char cell[9]; //9 cells per board
	signed char iswon; //nonzero if the game is won. -1 if tied, 1 if player1, 2 if player2
	flags opens; //bit flags indicating open cells
} *board;

typedef struct board_t board_t;

board init_board(flags p1movs, flags p2movs); //creates a board with the indicated moves
board dup_board(board b); //duplicates a board

char getpos(board b, int pos); //returns the player at pos. 0 if nobody, 1 if player1, 2 if player2
int isvalid(board b, int pos);//returns whether the cell at pos is open
void setpos(board b, int pos, char plr); //places player plr's mark on position pos in b, modifies opens and iswon

signed char setwon(board b); //sets the iswon variable of b and returns it. -1 if tie, 1 if p1, 2 if p2, 0 if no winner
flags setopens(board b); //sets the opens variable of b and returns it
flags getmovs(board b, char plr); //returns a flags of the cells that plr has marked.

char countopens(board b); //returns a count of the open cells
char countflags(flags f); //returns a count of the active flags in f
char flagdiff(flags a, flags b); //return the cell position where a and b differ, 99 if none

flags canwin(board b, char plyr, flags ignore); //checks for potential wins for player plyr, returns a flag value of the cells it finds (i.e., a cell that if plyr played there they would win), ignoring the ones indicated

void print_board(board b); //print the board to stderr
char xo(char p); //returns x for player1, o for player2, space for empty

#endif
