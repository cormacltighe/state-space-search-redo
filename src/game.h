#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
//#include "sss.h"
#include "search.h"
#include "nine.h"
#include "nsearch.h"
#include "diag.h"

extern char cpu_plyr; //which player is the cpu

void play();
void nplay(ushort depth);

#endif
