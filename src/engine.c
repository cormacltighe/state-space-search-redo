#include "engine.h"

const flags const cellflags[9] = {256,128,64,32,16,8,4,2,1};
const char const cellvals[9]= {3,2,3,2,4,2,3,2,3};

int isvalid(board b, int pos)
{
	return b->cell[pos]==0;
}

char getpos(board b, int pos)
{
	return b->cell[pos];
}

void setpos(board b, int pos, char plr)
{
	b->cell[pos]=plr;
	setopens(b);
	setwon(b);
}

signed char setwon(board b)
{
	char c0=b->cell[0],c1=b->cell[1],c2=b->cell[2],c3=b->cell[3],c4=b->cell[4],c5=b->cell[5],c6=b->cell[6],c7=b->cell[7],c8=b->cell[8];
	if(c0!=0)
	{
		if(c0==c1 && c1==c2)//***|---|---
		{
			//dbgfprintf(stderr,"win top row\n");
			b->iswon=c0;
			return c0;
		}
		if(c0==c3 && c3==c6)//*--|*--|*--
		{
			//dbgfprintf(stderr,"win left column\n");
			b->iswon=c0;
			return c0;
		}
		if(c0==c4 && c4==c8)//*--|-*-|--*
		{
			//dbgfprintf(stderr,"win top left to bottom right\n");
			b->iswon=c0;
			return c0;
		}
	}
	if(c1!=0 && c1==c4 && c4==c7)//-*-|-*-|-*-
	{
		//dbgfprintf(stderr,"win middle column\n");
		b->iswon=c1;
		return c1;
	}
	if(c3!=0 && c3==c4 && c4==c5)//---|***|---
	{
		//dbgfprintf(stderr,"win middle row\n");
		b->iswon=c3;
		return c3;
	}
	if(c2!=0 && c2==c4 && c4==c6)//--*|-*-|*--
	{
		//dbgfprintf(stderr,"win top right to bottom left\n");
		b->iswon=c2;
		return c2;
	}
	if(c8!=0)
	{
		if(c8==c7 && c7==c6)//---|---|***
		{
			//dbgfprintf(stderr,"win bottom row\n");
			b->iswon=c8;
			return c8;
		}
		if(c8==c5 && c5==c2)//--*|--*|--*
		{
			//dbgfprintf(stderr,"win right column\n");
			b->iswon=c8;
			return c8;
		}
	}
	if(c0!=0 && c1!=0 && c2!=0 && c3!=0 && c4!=0 && c5!=0 && c6!=0 && c7!=0 && c8!=0)//full, tie
	{
		//dbgfprintf(stderr,"tie\n");
		b->iswon=-1;
		return -1;
	}
	return 0;
}

flags setopens(board b)
{
	flags out=0;
	for(int i=0; i<9; i++)
	{
		if(b->cell[i]==0)
		{
			b->opens|=cellflags[i];
			out|=cellflags[i];
		}
	}
	return out;
}

char countopens(board b)
{
	char out=0;
	for(int i=0; i<9; i++)
	{
		if(isvalid(b,i))
		{
			out++;
		}
	}
	return out;
}

flags canwin(board b, char p, flags ignore)
{
	flags out=0;
	char c00=b->cell[0],c01=b->cell[1],c02=b->cell[2],c10=b->cell[3],c11=b->cell[4],c12=b->cell[5],c20=b->cell[6],c21=b->cell[7],c22=b->cell[8];//012|345|678
	if(c00==p || c10==p || c20==p)//left column
	{
		if(c00==p && c10==p && c20==0)
		{
			out|=cellflags[6];   //*--|*--|_--
		}
		if(c00==p && c10==0 && c20==p)
		{
			out|=cellflags[3];   //*--|_--|*--
		}
		if(c00==0 && c10==p && c20==p)
		{
			out|=cellflags[0];   //_--|*--|*--
		}
	}
	if(c01==p || c11==p || c21==p)//center column
	{
		if(c01==p && c11==p && c21==0)
		{
			out|=cellflags[7];   //-*-|-*-|-_-
		}
		if(c01==p && c11==0 && c21==p)
		{
			out|=cellflags[4];   //-*-|-_-|-*-
		}
		if(c01==0 && c11==p && c21==p)
		{
			out|=cellflags[1];   //-_-|-*-|-*-
		}
	}
	if(c02==p || c12==p || c22==p)//right column
	{
		if(c02==p && c12==p && c22==0)
		{
			out|=cellflags[8];   //--*|--*|--_
		}
		if(c02==p && c12==0 && c22==p)
		{
			out|=cellflags[5];   //--*|--_|--*
		}
		if(c02==0 && c12==p && c22==p)
		{
			out|=cellflags[2];   //--_|--*|--*
		}
	}
	if(c00==p || c01==p || c02==p)//top row
	{
		if(c00==p && c01==p && c02==0)
		{
			out|=cellflags[2];   //**_|---|---
		}
		if(c00==p && c01==0 && c02==p)
		{
			out|=cellflags[1];   //*_*|---|---
		}
		if(c00==0 && c01==p && c02==p)
		{
			out|=cellflags[0];   //_**|---|---
		}
	}
	if(c10==p || c11==p || c12==p)//middle row
	{
		if(c10==p && c11==p && c12==0)
		{
			out|=cellflags[5];   //---|**_|---
		}
		if(c10==p && c11==0 && c12==p)
		{
			out|=cellflags[4];   //---|*_*|---
		}
		if(c10==0 && c11==p && c12==p)
		{
			out|=cellflags[3];   //---|_**|---
		}
	}
	if(c20==p || c21==p || c22==p)//bottom row
	{
		if(c20==p && c21==p && c22==0)
		{
			out|=cellflags[8];   //---|---|**_
		}
		if(c20==p && c21==0 && c22==p)
		{
			out|=cellflags[7];   //---|---|*_*
		}
		if(c20==0 && c21==p && c22==p)
		{
			out|=cellflags[6];   //---|---|_**
		}
	}
	if(c00==p || c11==p || c22==p)//top left to bottom right
	{
		if(c00==p && c11==p && c22==0)
		{
			out|=cellflags[8];   //*--|-*-|--_
		}
		if(c00==p && c11==0 && c22==p)
		{
			out|=cellflags[4];   //*--|-_-|--*
		}
		if(c00==0 && c11==p && c22==p)
		{
			out|=cellflags[0];   //_--|-*-|--*
		}
	}
	if(c02==p || c11==p || c20==p)//top right to bottom left
	{
		if(c02==p && c11==p && c20==0)
		{
			out|=cellflags[6];   //--*|-*-|_--
		}
		if(c02==p && c11==0 && c20==p)
		{
			out|=cellflags[4];   //--*|-_-|*--
		}
		if(c02==0 && c11==p && c20==p)
		{
			out|=cellflags[2];   //--_|-*-|*--
		}
	}
	out&=(~ignore);
	return out;
}

char countflags(flags f)
{
	char out=0;
	for(int i=0; i<9; i++)
	{
		if(f&cellflags[i])
		{
			out++;
		}
	}
	return out;
}

board init_board(flags p1movs, flags p2movs)
{
	board b=calloc(1,sizeof(struct board_t));
	for(int i=0; i<9; i++)
	{
		if(p1movs&cellflags[i])
		{
			b->cell[i]=1;
		}
		if(p2movs&cellflags[i])
		{
			b->cell[i]=2;
			if(p1movs&cellflags[i])
			{
				abort();//something has gone very wrong
			}
		}
		if(!b->cell[i])
		{
			b->opens|=cellflags[i];
		}
	}
	setwon(b);
	return b;
}

board dup_board(board b)
{
	flags p1=getmovs(b,1);
	flags p2=getmovs(b,2);
	board o=init_board(p1,p2);
	return o;
}

flags getmovs(board b, char plr)
{
	flags out=0;
	for(int i=0; i<9; i++)
	{
		if(b->cell[i]==plr)
		{
			out|=cellflags[i];
		}
	}
	return out;
}

char flagdiff(flags a, flags b)
{
	for(char i=0; i<9; i++)
	{
		if((a&cellflags[(int)i])!=(b&cellflags[(int)i]))
		{
			return i;
		}
	}
	return 99;
}

char xo(char p)
{
	return (p==1?'x':(p==2?'o':' '));
}

void print_board(board b)
{
	fprintf(stderr,"%c|%c|%c\n-----\n%c|%c|%c\n-----\n%c|%c|%c\n",xo(b->cell[0]),xo(b->cell[1]),xo(b->cell[2]),xo(b->cell[3]),xo(b->cell[4]),xo(b->cell[5]),xo(b->cell[6]),xo(b->cell[7]),xo(b->cell[8]));
}
