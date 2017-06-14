#include "nine.h"

nboard init_nboard(nflags p1movs, nflags p2movs)
{
	nboard out=calloc(1,sizeof(nb_t));
	for(int i=0; i<9; i++)
	{
		out->bds[i]=init_board(p1movs.f[i],p2movs.f[i]);
		out->nopens.f[i]=setopens(out->bds[i]);
	}
	out->must=-1;
	return out;
}

nboard dup_nboard(nboard n)
{
	nboard out=calloc(1,sizeof(nb_t));
	for(int i=0; i<9; i++)
	{
		out->bds[i]=dup_board(n->bds[i]);
	}
	out->must=n->must;
	out->won=n->won;
	return out;
}

void free_nboard(nboard n)
{
	for(int i=0; i<9; i++)
	{
		free(n->bds[i]);
	}
	free(n);
}

char getnpos(nboard n, int bd, int pos)
{
	return getpos(n->bds[bd],pos);
}

void setnpos(nboard n, int bd, int pos, char plr)
{
	setpos(n->bds[bd],pos,plr);
	setnwon(n);
	if(countopens(n->bds[pos])>0)
	{
		n->must=pos;
	}
}

bool isnvalid(nboard n, int bd, int pos)
{
	return isvalid(n->bds[bd],pos);
}

signed char setnwon(nboard n)
{
	signed char out=0;
	for(int i=0; i<9; i++)
	{
		setwon(n->bds[i]);
		if(n->bds[i]->iswon!=0 && n->bds[i]->iswon!=-1)
		{
			out=n->bds[i]->iswon;
			n->won=out;
			return out;
		}
	}
	bool tie=true;
	for(int i=0; i<9; i++)
	{
		if(n->bds[i]->iswon!=-1)
		{
			tie=false;
			break;
		}
	}
	if(tie)
	{
		n->won=-1;
		return -1;
	}
	return 0;
}

nflags setnopens(nboard n)
{
	nflags o= {.f={0,0,0,0,0,0,0,0,0}};
	for(int i=0; i<9; i++)
	{
		o.f[i]=setopens(n->bds[i]);
	}
	n->nopens=o;
	return o;
}

void print_nboard(nboard n)
{
	for(int bigrow=0; bigrow<3; bigrow++)//rows in the nineboard
	{
		for(int subrow=0; subrow<3; subrow++)//rows in each sub-board
		{
			for(int bd=0; bd<3; bd++)//sub-boards in the super-rows
			{
				fprintf(stderr,"%c|%c|%c",xo(n->bds[3*bigrow+bd]->cell[3*subrow+0]),xo(n->bds[3*bigrow+bd]->cell[3*subrow+1]),xo(n->bds[3*bigrow+bd]->cell[3*subrow+2]));
				if(bd!=2)
				{
					fprintf(stderr,"\u2588\u2588");
				}
				else
				{
					fprintf(stderr,"\n");
				}
			}
			if(subrow!=2)
			{
				fprintf(stderr,"-----\u2588\u2588-----\u2588\u2588-----\n");
			}
		}
		if(bigrow!=2)
		{
			fprintf(stderr,"\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\n");
		}
	}
}
