#ifndef NSEARCH_H
#define NSEARCH_H

#include <limits.h>
#include "nine.h"
#include "engine.h"
#include "diag.h"

#define NO_LIMIT USHRT_MAX
#define isint(x) ((int)x==x)

//extern unsigned long long prun;

//typedef enum {LOSE=-1,
typedef unsigned short ushort;
typedef struct
{
	int bd;
	char mov;
	float util;
} nret;//move indicator. using floats here for heuristics. terminal utilities are integer -1/0/1 and any non-integer values are heuristics
typedef struct
{
	float a;
	float b;
} bound;//alpha and beta bounds for alpha-beta pruning

extern const float cellheur[9];

nret nsearch(nboard n, char cpu, char just, int jbd, char jmov, char nxt, bool dmax, ushort depth, bound ab);//recurses at most depth levels unless depth==NO_LIMIT. performs alpha-beta pruning
nret ncpu_move(nboard n, char cpu, ushort depth);//pick the cpu's move
float heur(nboard n, char cpu, int bd, char mov, char plr);//calculate the heuristic value of the indicated move for player plr

#endif
