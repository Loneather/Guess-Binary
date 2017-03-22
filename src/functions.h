#ifndef __FUNCTIONS__
#define __FUNCTIONS__

int random0or1(void);
int fitness(int * , int * ,int );
double random0to1(void);
int rand_interval(int );
void merge_temp(int **,int **,int  ,int ); 
void clear_array_2d(int **,int ,int );
void clear_array_1d(double *x,int size);
void init_population(int **,int  ,int );
double get_average_population(int **,int  *,int  ,int );
int get_max_member(int **,int *,int ,int ,int *);

#endif