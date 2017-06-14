#include "search.h"

ret search(board b, char cpu, char just, char move, char nxt, bool dmax)
{
	ret out= {.mov=0, .util=(dmax?-99:99)};
	board d=dup_board(b);
	setpos(d,move,just);
	if(d->iswon)
	{
		out.mov=move;
		if(d->iswon==cpu)
		{
			out.util=1;
		}
		else if(d->iswon==-1)
		{
			out.util=0;
		}
		else
		{
			out.util=-1;
		}
		free(d);
		return out;
	}
	for(int i=0; i<9; i++)
	{
		ret tmp= {.mov=-1,.util=(dmax?-99:99)};
		if(isvalid(d,i))
		{
			tmp=search(d,cpu,nxt,i,just,!dmax);
			if(dmax)
			{
				if(tmp.util>out.util)
				{
					out.mov=i;
					out.util=tmp.util;
				}
			}
			else
			{
				if(tmp.util<out.util)
				{
					out.mov=i;
					out.util=tmp.util;
				}
			}
		}
	}
	free(d);
	return out;
}

ret cpu_move(board b, char cpu)
{
	ret out= {.mov=0, .util=-99};
	for(int i=0; i<9; i++)
	{
		if(isvalid(b,i))
		{
			ret tmp=search(b,cpu,cpu,i,cpu==1?2:1,false);
			if(tmp.util>out.util)
			{
				out.util=tmp.util;
				out.mov=i;
			}
			if(tmp.util==out.util && cellvals[i]>cellvals[(int)out.mov])//if the cell just searched has equal value to the current max, pick the one with the best strategic position (see engine.h)
			{
				out.mov=i;
			}
		}
	}
	return out;
}
