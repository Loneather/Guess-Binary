#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"
#include "genoperators.h"

const int POPL = 10 ;
const int GENS = 50 ;
const double p_mut = 0.1 ;
const double p_cross = 0.3 ;
const double p_tourn = 0.65 ;

int main(int argc ,char *argv[])
{
	if (argc > 2)
	{
		srand(atoi(argv[2]));
	}
	else
		srand(time(NULL));


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
	for (i = 0; i < GENS + 1; ++i)
	{
		maxf_archive[i] = 0 ;
	}
	double avf_archive[GENS+1] ;
	double bins[POPL + 1] ;

	double fitsum ,check_cross ;
	int    gencount = 0 ;
	int    counta ,countb ;
	int    max_place ;
	int    findmax ,findplace ;
	double average ;

	clear_array_2d(f_archive,GENS+1,LENGTH);
	clear_array_1d(avf_archive,GENS+1);


	/* Initialize population */
	init_population(population,POPL,LENGTH);

	average = get_average_population(population,specimen,POPL,LENGTH);
	get_max_member(population,specimen,POPL,LENGTH,&max_place);
	maxf_archive[0] = fitness(specimen,population[max_place],LENGTH);
	/* Saves max population */
	for (i = 0; i < LENGTH; ++i)
	{
		f_archive[gencount][i] = population[max_place][i] ;
	}
	gencount++;	

	/* Start of evolution proccess */
	while(gencount < GENS)
	{
		
		clear_array_1d(bins,POPL);
		clear_array_2d(temppop,POPL,LENGTH);
		for (i = 0; i < POPL; ++i)

		/* Start of selection proccess */
		fitsum = 0.0 ;
		for (i = 0; i < POPL; ++i)
		 {
		 	fitsum += fitness(specimen ,population[i] ,LENGTH) ;
		 } 

		/* Create ranges */
		bins[0] = 0 ;
		for (i = 1; i < POPL + 1; ++i)
		{
			bins[i] = (fitness(specimen,population[i - 1],LENGTH) / fitsum) + bins[i-1] ; 
		}


		roullete_wheel_selection(temppop,POPL,LENGTH,population,bins);
		tournament_selection(temppop,specimen,POPL,LENGTH,p_tourn);

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
		
		
		average = get_average_population(population,specimen,POPL,LENGTH);
		maxf_archive[gencount] = get_max_member(population,specimen,POPL,LENGTH,&max_place);
		for (i = 0; i < LENGTH; ++i)
		{
			f_archive[gencount][i] = population[max_place][i] ; /* Store fittest */
		}
		
		/* Print the results of current generation */		
		printf("Generation %d: Best Fitness = %d  Average Fitness = %04.4f \n" ,gencount ,maxf_archive[gencount] ,average);
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
			printf("\nFitness = %d  (%d matches out of %d)\n",maxf_archive[gencount] ,((int) sqrt(maxf_archive[gencount])),LENGTH);
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
	printf("\nFitness = %d  (%d matches out of %d)\n",maxf_archive[findplace] ,((int) sqrt(maxf_archive[findplace])),LENGTH);
	return 1 ;
}
