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
void roullete_wheel_selection(int *temppop,int size,int length,int *population,int *bins)
{
	double check_sel ;
	int tempcount ;

	tempcount = 0 ;
	for (itempcount = 0; tempcount < size; ++tempcount)
	{
	 	check_sel = random0to1() ;
	 	for (i = 1; i < size + 1; ++i)
	 	{
	 		if (check_sel > bins[i - 1] && check_sel < bins[i])
	 		{
	 			for (j = 0; j < length; ++j)
	 			{
	 				temppop[i][j] = population[i][j] ;
	 			}
	 		}
	 	}
	}
}
void tourname_selection(int competitors,int size ,int length)
{

	
}