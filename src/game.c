//#include <limits.h>
#include "game.h"
//#include "engine.h"
//#include "search.h"

char cpu_plyr;

void play()
{
	char buf[100];
	char user_is='w';
	char *stop_bugging_me=NULL;
	do
	{
		fprintf(stderr,"What would you like to play as (x/o): ");
		//scanf("%s",buf);//&user_is);
		stop_bugging_me=fgets(buf,100,stdin);
		user_is=buf[0];
		if(user_is!='x' && user_is!='X' && user_is!='o' && user_is!='O')
		{
			fprintf(stderr,"please indicate x or o.\n");
			user_is='w';
			//scanf("%s"
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
	board b=init_board(0,0);
	//node root=stree_init(cpu_plyr,cpu_plyr==1);//stree_pop(start,cpu_plyr,0,0,1,cpu_plyr==1);
	//node curr=root;
	int mpt[9]= {1,1,1,1,1,1,1,1,1};
	char whose_turn=1;
	while(!b->iswon)//!curr->isterm)
	{
		print_board(b);//curr->s);
		if(cpu_plyr==whose_turn)
		{
			//node next=curr->chil[curr->best_child];
			ret mv=cpu_move(b,cpu_plyr);
			char mov=mv.mov;//flagdiff(curr->s->opens,next->s->opens);
			//curr=next;
			mpt[(int)mov]=0;
			printf("%hhd\n",mov+1);
			fprintf(stderr,"computer moves in cell %hhd\n",mov+1);
			//print_board(curr->s);
			setpos(b,mov,whose_turn);
		}
		else
		{
			char mov=10;
			do
			{
				fprintf(stderr,"where would you like to move (");
				bool hv=false;
				for(int i=0; i<9; i++)
				{
					if(!hv&&mpt[i])
					{
						fprintf(stderr,"%d",i+1);
						hv=true;
					}
					else if(mpt[i])
					{
						fprintf(stderr,", %d",i+1);
					}
				}
				fprintf(stderr,")? : ");
				//scanf("%s",buf);
				stop_bugging_me=fgets(buf,100,stdin);
				int zz=atoi(buf);
				if(zz>CHAR_MAX || zz<CHAR_MIN)
				{
					mov=99;
				}
				else
				{
					mov=(char)zz;
				}
				//scanf("%hhd",&mov);
				mov--;
				if(mov>8 || mov<0)
				{
					fprintf(stderr,"you must enter a number between 1 and 9\n");
					mov=10;
					continue;
				}
				if(!isvalid(b,mov))//curr->s,mov))
				{
					fprintf(stderr,"that cell is already occupied\n");
					mov=10;
					continue;
				}
			}
			while(0>mov || 8<mov || !isvalid(b,mov)); //curr->s,mov));
			/*for(int i=0; i<curr->nchil; i++)
			{
				node next=curr->chil[i];
				if(flagdiff(curr->s->opens,next->s->opens)==mov)
				{
					curr=next;
					break;
				}
			}*/
			setpos(b,mov,whose_turn);
			mpt[(int)mov]=0;
		}
		/*setopens(b);
		setwon(b);
		fprintf(stderr,"diagnostic: all cells\n");
		for(int i=0; i<9; i++)
		{
			fprintf(stderr,"%d: %d\n",i+1,b->cell[i]);
		}
		fprintf(stderr,"valid cells: ");
		for(int i=0; i<9; i++)
		{
			if(isvalid(b,i))
			{
				fprintf(stderr,"%d,",i+1);
			}
		}
		fprintf(stderr,"\n");*/
		print_board(b);//curr->s);
		fprintf(stderr,"\n");
		whose_turn=(whose_turn==1?2:1);
	}
	if(!b->iswon)//curr->isterm)
	{
		//shit
		fprintf(stderr,"Something went wrong\n");
		print_board(b);
		fprintf(stderr,"this should have been a terminal state, but the loop exited early apparently\n");
		abort();
	}
	//fprintf(stderr,"%s\n",curr->s->iswon==1?"X won":(curr->s->iswon==2?"O won":"Tie"));
	fprintf(stderr,"%s\n",b->iswon==1?"X won":(b->iswon==2?"O won":"Tie"));
	print_board(b);//curr->s);
	//stree_free(root);
	free(b);
	if(stop_bugging_me==NULL)
	{
		//shut up
	}
}
