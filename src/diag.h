#ifndef DIAG_H
#define DIAG_H

//header for runtime-diagnostics and statistics

#include <stdarg.h>
#include <stdio.h>

typedef enum {STATS=1,BASIC,MORE,ALL} vlevel;

extern int verb; //the verbosity level
extern unsigned long long prun; //the number of times pruning took place
extern unsigned long long total_prun; //the total number of prunings in the game as a whole
extern unsigned long long heur_eval; //the number of times a node was heuristically evaluated
extern unsigned long long term_eval; //the number of times a node was a terminal node
extern unsigned long long total_heur_eval; //total number of heuristis evaluations
extern unsigned long long total_term_eval; //total number of terminal evaluations
extern unsigned long long nods; //the number of nodes visited in a call
extern unsigned long long total_nods; //total number of nodes visited in the game
void dpnt(vlevel level, const char *format, ...); //print the message to stderr if verb>=level, do nothing otherwise

#endif
