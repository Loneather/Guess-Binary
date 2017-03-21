#include "guessga.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int random0or1(){
    
    if (rand() % 2 == 0)
    {
        return 1 ;
    }
    else 
        return 0 ;

}

/* Fitness function F = k^2 ,where k number of equal bits */
int fitness(int *purespecimen , int *checkspecimen ,int length){
    int k , i ;
    k = 0 ;
    for (i = 0; i < length; ++i)
    {
        if (purespecimen[i] == checkspecimen[i])
        {
            k++;
        }
    }
    return (k*k) ;
}

double random0to1(){
    double getrandom ;
    getrandom = rand() ;

    if(getrandom != RAND_MAX )
        return getrandom / RAND_MAX;
    else
        return random0to1() ;
}

int rand_interval(int max){ /* Source : lists.di.uoa.gr */
	int random ;
	const int range = 1 + max ;
    const int buckets = RAND_MAX / range ;
    const int limit = buckets * range ;
    do
    {
    	random = rand() ;
    }while(random >= limit);

    return (random / buckets) ;
}

/* Swaps the values of the 2 arrays up to cross */
void crossover(int *a,int *b ,int length){	
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

