#include "guessga.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

const int POPL = 10 ;
const int GENS = 50 ;
const double p_mut = 0.1 ;
const double p_cross = 0.3 ;
const double p_tourn = 0.65 ;

int main(void)
{
	int   i ,FITTEST = 0 ;
	char  ch = 0 ;
	int   char_count = 0 ,LENGTH = 0 ,buf[100];

	printf("Give number for programm to find ");
	for (i = 0; i < 100; ++i)
	{
		scanf("%c" ,&ch);
		if (ch == '\n' || ch == EOF)
		{
			break ;
		}
		else{
			buf[i] = ch - '0' ;
			char_count++;
		}
	}

	LENGTH = char_count ;
	FITTEST = LENGTH * LENGTH ;
	int specimen[LENGTH] ;
	for (i = 0; i < LENGTH; ++i)
	{
		specimen[i] = buf[i] ;
	}

    int **population = (int **)malloc(POPL * sizeof(int *));
    for (i=0; i<POPL; i++)
         population[i] = (int *)malloc(LENGTH * sizeof(int));

    int **temppop = (int **)malloc(POPL * sizeof(int *));
    for (i=0; i<POPL; i++)
         temppop[i] = (int *)malloc(LENGTH * sizeof(int));

    int **f_archive = (int **)malloc((GENS+1) * sizeof(int *));
    for (i=0; i<(GENS+1); i++)
         f_archive[i] = (int *)malloc(LENGTH * sizeof(int));

	int    maxf_archive[GENS+1] ;
	double avf_archive[GENS+1] ;
	double bins[POPL] ;

	double fitsum ;
	double sumofbins = 0 ;
	double check_sel = 0 ,check_cross = 0 ,check_mut = 0 ,check_tour = 0;
	int    gencount = 0 ;
	int    k ,j ;
	int    tempcount ,counta ,countb ;
	int    fit_temp = 0 ,champ_a = 0 ,champ_b = 0 ;
	int    max_place ;
	int    findmax ,findplace ;

	srand(time(NULL)) ;

	for (i = 0; i < GENS + 1; ++i)
	{
		for (j = 0;j < LENGTH; ++j)
		{
			f_archive[i][j] = 0 ;
		}
	}

	/* Set values for maximum fitness and average fitness arrays */
	for (i = 0; i < GENS + 1; ++i)
	{
		maxf_archive[i] = -1 ;
		avf_archive[i] = 0.0 ;
	}

	/* Initialize population */
	for (i = 0; i < POPL; ++i)
	{
		for (j = 0; j < LENGTH; ++j)
		{
			population[i][j] = random0or1() ; 
		}
	}

	/*Find fittest and average of the 0th generation */
	max_place = 0 ;
	for (i = 0; i < POPL; ++i)
	{
		fit_temp = fitness(specimen,population[i],LENGTH);
		avf_archive[gencount] += fit_temp ;
		if (fit_temp > maxf_archive[gencount])
		{
			maxf_archive[gencount] = fit_temp ;
			max_place = i ;
		}
	}
	avf_archive[gencount] = avf_archive[gencount] / ((double) POPL) ;

	/* Saves max population */
	for (i = 0; i < LENGTH; ++i)
	{
		f_archive[gencount][i] = population[max_place][i] ;
	}
	gencount++;	

	/* Start of evolution proccess */
	while(gencount < GENS)
	{
		
		clear_array(bins,1,POPL);
		clear_array(temppop,POPL,LENGTH);
		for (i = 0; i < POPL; ++i)

		/* Start of selection proccess */
		fitsum = 0.0 ;
		for (i = 0; i < POPL; ++i)
		 {
		 	fitsum += fitness(specimen ,population[i] ,LENGTH) ;
		 } 

		/* Create ranges */
		sumofbins = 0 ;
		for (i = 0; i < POPL; ++i)
		{
			bins[i] = (fitness(specimen ,population[i] ,LENGTH) / fitsum) + sumofbins ;
			sumofbins += (fitness(specimen ,population[i] ,LENGTH) / fitsum) ;
		}

		/* Create temporary population */
		tempcount = 0 ;
		while(tempcount < POPL)
		{
		 	check_sel = random0to1() ;
		 	for (i = 0; i < POPL; ++i)
		 	{
		 		if (i == 0 )
		 		{
		 			if (0 <= check_sel && check_sel < bins[i] )
		 			{
		 				for (k = 0; k < LENGTH; ++k)
		 				{
		 					temppop[tempcount][k] = population[i][k] ;
		 				}
		 				tempcount++;
		 			}
		 		}
		 		else
		 		{
		 			if (bins[i-1] <= check_sel && check_sel < bins[i]){
		 				for (k = 0; k < LENGTH; ++k)
		 					{
								temppop[tempcount][k] = population[i][k] ;
		 					}
		 				tempcount++;
		 			}
		 		}
		 	}
		}

		/* Tournament Selection */
		/* See README for details on method */
		for (i = 0; i < POPL/2; ++i)
		{
			check_tour = random0to1() ;
			champ_a = fitness(specimen,temppop[i],LENGTH);
			champ_b = fitness(specimen,temppop[POPL - 1 - i],LENGTH) ;
			if (check_tour < p_tourn)
			{
				if (champ_a > champ_b )
				{
					for (j = 0; j < LENGTH; ++j)
					{
						temppop[POPL - 1 - i][j] = temppop[i][j];
					}
				}
				else
					for (j = 0; j < LENGTH; ++j)
					{
						temppop[i][j] = temppop[POPL - 1 - i][j];
					}
			}
			else
			{
				if (champ_a < champ_b )
				{
					for (j = 0; j < LENGTH; ++j)
					{
						temppop[POPL - 1 - i][j] = temppop[i][j];
					}
				}
				else
					for (j = 0; j < LENGTH; ++j)
					{
						temppop[i][j] = temppop[POPL - 1 - i][j];
					}
			}
		}

		/* Crossover */ 
		counta = 0 ;
		countb = 1 ;
		for (i = 0; i < POPL / 2; ++i)
		{
			check_cross = random0to1() ;
			if (check_cross < p_cross)
			{
				crossover(temppop[counta],temppop[countb],LENGTH) ;
			}
			counta = counta + 2 ;
			countb = countb + 2 ;
		}

		/* Mutation */
		for (i = 0; i < POPL; ++i)
		{
			mutate(temppop[i],LENGTH,p_mut);
		}

		merge_temp(temppop,population,POPL,LENGTH);
		
		/* Find fittest and average of this population */
		max_place = 0 ;
		for (i = 0; i < POPL; ++i)
		{
			fit_temp = fitness(specimen,population[i],LENGTH);
			avf_archive[gencount] = avf_archive[gencount] + fit_temp ;
			if (fit_temp > maxf_archive[gencount])
			{
				maxf_archive[gencount] = fit_temp ;
				max_place = i ;
			}
		}
		avf_archive[gencount] = avf_archive[gencount] / ((double) POPL) ;
		for (i = 0; i < LENGTH; ++i)
		{
			f_archive[gencount][i] = population[max_place][i] ;
		}
		
		/* Print the results of current generation */		
		printf("Generation %d: Best Fitness = %d  Average Fitness = %04.4f \n" ,gencount ,maxf_archive[gencount] ,avf_archive[gencount]);
		if (maxf_archive[gencount] >= FITTEST)
		{
			printf("\nYour number : ");
			for (i = 0; i < LENGTH; ++i)
			{
				printf("%d",specimen[i]) ;
			}
			printf("\nMy guess is : ");
			for (i = 0; i < LENGTH; ++i)
			{
				printf("%d",f_archive[gencount][i]) ;
			}
			printf("\nFound in generation %d", gencount);
			printf("\nFitness = %d  (%d matches out of %d)\n",maxf_archive[gencount] ,((int) sqrt(((double) maxf_archive[gencount]))),LENGTH);
			return 2 ;
		}
		gencount++;
	}
	/* Find max of all generations */
	findmax = maxf_archive[0] ;
	findplace = 0 ;
	for (i = 1; i < GENS+1; ++i)
	{
		if (maxf_archive[i] > findmax)
		{
			findmax = maxf_archive[i] ;
			findplace = i ;
		}
	}
	printf("\nYour number : ");
	for (i = 0; i < LENGTH; ++i)
	{
		printf("%d",specimen[i]) ;
	}
	printf("\nMy guess is : ");
	for (i = 0; i < LENGTH; ++i)
	{
		printf("%d",f_archive[findplace][i]) ;
	}
	/* Print results */
	printf("\nFound in generation %d", findplace);
	printf("\nFitness = %d  (%d matches out of %d)\n",maxf_archive[findplace] ,((int) sqrt(((double) maxf_archive[findplace]))),LENGTH);
	return 1 ;
}
