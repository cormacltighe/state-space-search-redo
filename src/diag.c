#include "diag.h"

int verb=0;

unsigned long long prun=0;
unsigned long long total_prun=0;
unsigned long long heur_eval=0;
unsigned long long term_eval=0;
unsigned long long total_heur_eval=0;
unsigned long long total_term_eval=0;
unsigned long long nods=0;
unsigned long long total_nods=0;

void dpnt(vlevel level, const char *format, ...)
{
	if(verb>=level)
	{
		va_list list;
		va_start(list,format);
		vfprintf(stderr,format,list);
		va_end(list);
	}
}
