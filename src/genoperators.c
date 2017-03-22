#include <stdio.h>

#include "genoperators.h"
#include "functions.h"

void mutate(int *x,int size,double p_mut)
{
	double p = random0to1();
	int place ; 

	place = rand_interval(size - 1);
	if (p < p_mut)
	{
		x[place] = (x[place] ? 0 : 1);
	}
}
void roullete_wheel_selection(int **temppop,int size,int length,int **population,double *bins)
{
	double check_sel ;
	int tempcount ,i ,j ;

	tempcount = 0 ;
	for (tempcount = 0; tempcount < size; ++tempcount)
	{
	 	check_sel = random0to1() ;
	 	for (i = 1; i < size + 1; ++i)
	 	{
	 		if (check_sel > bins[i - 1] && check_sel < bins[i])
	 		{
	 			for (j = 0; j < length; ++j)
	 			{
	 				temppop[tempcount][j] = population[i - 1][j] ;
	 			}
	 		}
	 	}
	}
}
void tournament_selection(int **competitors,int *specimen,int size ,int length,double p_tourn)
{
	double check_tour ;
	int champ_a ,champ_b ;
	int i ,j ;
	for (i = 0; i < size/2; ++i)
	{
		check_tour = random0to1() ;
		champ_a = fitness(specimen,competitors[i],length);
		champ_b = fitness(specimen,competitors[size - 1 - i],length) ;
		if (check_tour < p_tourn) /* Fittest won */
		{
			if (champ_a > champ_b )
			{
				for (j = 0; j < length; ++j)
				{
					competitors[size - 1 - i][j] = competitors[i][j];
				}
			}
			else
				for (j = 0; j < length; ++j)
				{
					competitors[i][j] = competitors[size - 1 - i][j];
				}
		}
		else				/* Less fit won */
		{
			if (champ_a < champ_b )
			{
				for (j = 0; j < length; ++j)
				{
					competitors[size - 1 - i][j] = competitors[i][j];
				}
			}
			else
				for (j = 0; j < length; ++j)
				{
					competitors[i][j] = competitors[size - 1 - i][j];
				}
		}
	}
}
void crossover(int *a,int *b ,int length)
{	
    int cross = rand_interval(length - 1) ;
    int temp[length] ;
    
    int i ;
    for (i = 0; i < cross; ++i)	
    {
        temp[i] = a[i] ;
        a[i] = b[i] ;
        b[i] = temp[i] ;
    }
}