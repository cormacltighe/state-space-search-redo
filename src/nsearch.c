#include "nsearch.h"
//unsigned long long prun=0;
const float cellheur[9]= {2/6.0,1/6.0,2/6.0,1/6.0,3/6.0,1/6.0,2/6.0,1/6.0,2/6.0};

nret nsearch(nboard n, char cpu, char just, int jbd, char jmov, char nxt, bool dmax, ushort depth, bound ab)
{
	//oh boy this is going to get ugly fast
	//nret out={.bd=jbd, .mov=jmov, .util=(dmax?ab.a:ab.b)};
	nods++;
	total_nods++;
	nret out= {.bd=jbd, .mov=jmov, .util=(dmax?-99.0:99.0)};
	nboard nn=dup_nboard(n);
	setnpos(nn,jbd,jmov,just);
	if(nn->won)
	{
		term_eval++;
		total_term_eval++;
		if(nn->won==cpu)
		{
			out.util=1.0;
		}
		else if(nn->won==-1)
		{
			out.util=0.0;
		}
		else
		{
			out.util=-1.0;
		}
		free_nboard(nn);
		return out;
	}
	if(depth==0)
	{
		heur_eval++;
		total_heur_eval++;
		out.util=heur(n,cpu,jbd,jmov,just);
		free_nboard(nn);
		return out;
	}
	//bound bb=ab;
	for(int b=0; b<9; b++)
	{
		if(nn->must!=-1)
		{
			b=nn->must;
		}
		for(int i=0; i<9; i++)
		{
			nret tmp= {.bd=b, .mov=-1, .util=(dmax?-99.0:99.0)};
			//bound bb={.a=(dmax?(out.util):(ab.a)), .b=(dmax?(ab.b):(out.util))};
			if(isnvalid(nn,b,i))
			{
				tmp=nsearch(nn,cpu,nxt,b,i,just,!dmax,(depth==NO_LIMIT?depth:depth-1),ab);
				if(dmax)
				{
					if(tmp.util>out.util)
					{
						out.util=tmp.util;
						out.bd=b;//tmp.bd;
						out.mov=i;//tmp.mov;
					}
					if(out.util>ab.a)
					{
						ab.a=out.util;
					}
					if(ab.b<=ab.a)
					{
						prun++;
						total_prun++;
						goto outlp;
					}
					/*if(tmp.util>ab.a)
					{
						ab.a=tmp.util;
					}*/
				}
				else
				{
					if(tmp.util<out.util)
					{
						out.util=tmp.util;
						out.bd=b;
						out.mov=i;
					}
					if(out.util<ab.b)
					{
						ab.b=out.util;
					}
					if(ab.a>=ab.b)
					{
						prun++;
						total_prun++;
						goto outlp;
					}
					/*if(tmp.util<ab.b)//maybe
					{
						ab.b=tmp.util;
					}*/
				}
			}
		}
outlp:
		if(nn->must!=-1)
		{
			b=99;
		}
	}
	free_nboard(nn);
	return out;
	//actually, that wasn't that bad
}

nret ncpu_move(nboard n, char cpu, ushort depth)
{
	nret out= {.bd=0, .mov=0, .util=-99.0};
	nret tmp= {.bd=0, .mov=0, .util=-99.0};
	nods++;
	total_nods++;
	bound ab= {.a=-99.0,.b=99.0};
	if(n->must!=-1)
	{
		#pragma omp parallel for
		for(int i=0; i<9; i++)
		{
			if(isnvalid(n,n->must,i))
			{
				tmp=nsearch(n,cpu,cpu,n->must,i,cpu==1?2:1,false,depth,ab);
				if(tmp.util>out.util)
				{
					out.util=tmp.util;
					out.bd=n->must;
					out.mov=i;
				}
			}
		}
	}
	else
	{
		for(int b=0; b<9; b++)
		{
			#pragma omp parallel for
			for(int i=0; i<9; i++)
			{
				if(isnvalid(n,b,i))
				{
					tmp=nsearch(n,cpu,cpu,b,i,cpu==1?2:1,false,depth,ab);
					if(tmp.util>out.util)
					{
						out.util=tmp.util;
						out.bd=b;
						out.mov=i;
					}
				}
			}
		}
	}
	return out;
}

float heur(nboard n, char cpu, int bd, char mov, char plr)
{
	flags fwin=canwin(n->bds[bd],plr,0);
	//flags floss=canwin(n->bds[bd],plr==1?2:1,cellflags[(int)mov]);
	//flags flosswo=canwin(n->bds[bd],plr==1?2:1,0);
	flags onefut=canwin(n->bds[(int)mov],plr==1?2:1,0);
	if(fwin&cellflags[(int)mov])//if i play mov will i immediately win?
	{
		return plr==cpu?1.0:-1.0;
	}
	if(countflags(onefut))//if i make this move will i allow the other player to win next turn?
	{
		return plr==cpu?-1.0:1.0;
	}
	/*if(flagdiff(floss,flosswo)==mov)//if i play mov will i block the other player from winning?
	{
		return 3.0/4.0;
	}*/
	//fprintf(stderr,"heur: ");
	float out=cellheur[(int)mov];
	if(plr!=cpu)
	{
		fprintf(stderr,"heur for not cpu\n");
		out=1.0-out;
		out-=2.0/6.0;
		abort();
	}
	//fprintf(stderr,"\n");
	return out;
}
