#include "game.h"


int main(int argc, char **argv)
{
	if(argc>1)
	{
		if(argv[1][0]=='s' || argv[1][0]=='S')
		{
			verb=STATS;
		}
		nplay(10);
	}
	else
	{
		while(1)
		{
			play();
		}
	}
}
