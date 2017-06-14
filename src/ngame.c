#include "game.h"

//#define DEPTH 20

void nplay(ushort depth)
{
	char buf[100];
	char user_is='w';
	char *stfu=NULL;
	int total_moves=0;
	do
	{
		fprintf(stderr,"What would you like to play as? (x/o): ");
		stfu=fgets(buf,100,stdin);
		user_is=buf[0];
		if(user_is!='x' && user_is!='X' && user_is!='o' && user_is!='O')
		{
			fprintf(stderr,"please indicate x or o.\n");
			user_is='w';
		}
	}
	while(user_is=='w');
	if(user_is=='x' || user_is=='X')
	{
		cpu_plyr=2;
	}
	else
	{
		cpu_plyr=1;
	}
	fprintf(stderr,"your input must be two numbers one through nine separated by a comma, e.g., \"2,3\".\nThe first number is the board, the second is the cell in that board\n");
	nflags nf= {.f={0,0,0,0,0,0,0,0,0}};
	nboard n=init_nboard(nf,nf);
	char whose=1;
	while(!n->won)
	{
		total_moves++;
		print_nboard(n);
		fprintf(stderr,"\n");
		if(cpu_plyr==whose)
		{
			nret mv=ncpu_move(n,cpu_plyr,depth);
			if(depth!=NO_LIMIT && total_moves%6==0)
			{
				//depth++;//too much
				depth+=2;
			}
			int bdmv=mv.bd;
			char mov=mv.mov;
			printf("%d,%d\n",bdmv+1,mov+1);
			dpnt(STATS,"%lld nodes explored. %lld total evaluations. %lld heuristic evaluations (%f%%), %lld terminal evaluations (%f%%). alpha-beta has pruned %lld times\n",nods,heur_eval+term_eval,heur_eval,((double)heur_eval)/(heur_eval+term_eval)*100.0,term_eval,((double)term_eval)/(heur_eval+term_eval)*100.0,prun);
			nods=0;
			prun=0;
			term_eval=0;
			heur_eval=0;
			fprintf(stderr,"computer moves in %d,%d\n",bdmv+1,mov+1);
			setnpos(n,bdmv,mov,whose);
		}
		else
		{
			char mov=10;
			int bd=10;
			do
			{
				fprintf(stderr,"where would you like to move?\n");
				if(n->must==-1)
				{
					fprintf(stderr,"you may play on any board. board first 1-9,1-9: ");
				}
				else
				{
					fprintf(stderr,"you must play on board %d. board first %d,1-9: ",n->must+1,n->must+1);
				}
				stfu=fgets(buf,100,stdin);
				sscanf(buf,"%d,%hhd",&bd,&mov);
				bd--;
				mov--;
				if(mov>8 || mov<0)
				{
					fprintf(stderr,"you must enter 2 numbers between 1 and 9 separated by a comma, where the first is the board\n");
					mov=10;
					continue;
				}
				if(bd>8 || bd<0)
				{
					fprintf(stderr,"you must enter 2 numbers between 1 and 9 separated by a comma, where the first is the board\n");
					bd=10;
					continue;
				}
				if(!isnvalid(n,bd,mov))
				{
					fprintf(stderr,"you cannot play there\n");
					mov=10;
					bd=10;
					continue;
				}
				if(n->must!=-1 && bd!=n->must)
				{
					fprintf(stderr,"you cannot play on that board\n");
					bd=10;
					continue;
				}
			}
			while(0>mov || 0>bd || 8<mov || 8<bd || !isnvalid(n,bd,mov));
			setnpos(n,bd,mov,whose);
		}
		fprintf(stderr,"\n");
		print_nboard(n);
		fprintf(stderr,"\n");
		if(n->must==-1)
		{
			fprintf(stderr,"the next player may play on any board\n\n");
		}
		else
		{
			fprintf(stderr,"the next player must play on board %d\n\n",n->must+1);
		}
		whose=(whose==1?2:1);
	}
	if(!n->won)
	{
		fprintf(stderr,"something went wrong, loop exited early\n");
		print_nboard(n);
		abort();
	}
	fprintf(stderr,"%s\n",n->won==1?"X won":(n->won==2?"O won":"Tie"));
	print_nboard(n);
	dpnt(STATS,"over %d turns there were: %lld total nodes visited, %lld total heuristic evaluations, %lld total terminal evaluations, and alpha-beta pruning was used %lld times.\n",total_moves,total_nods,total_heur_eval,total_term_eval,total_prun);
	free_nboard(n);
	if(stfu==NULL)
	{
		//
	}
}
