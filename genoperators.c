#include "genoperators.h"

void mutate(int *x,int size,double p_mut)
{
	p = random0to1();
	place = rand_interval(size - 1)
	if (p < p_mut)
	{
		x[place] = (x[place] ? 0 : 1);
	}
}