# Guess-Binary
--DIRECTORIES-- 
/src/	contains the source files for the programm.
		*guessgafun.c contains the main functions and others
		*functions.c contains the functions used by guessga 
/obj/	contains the object files of the above source-files 
/bin/	contains the executable file
--COMPILATION
when in folder src run the following commands 
--$ gcc -c guessga.c -o ../obj/guessga.o -lm 
--$ gcc -c functions.c -o ../obj/functions.o 
change folder to obj and run 
--$ gcc functions.o guessga.o -o ../bin/guessga -lm 
to run the programm change directory to bin and run normally 
--DESCRIPTION
All the parameters are determined as constants NOT as macros   . 
The number that this genetic algorithm is to guess is given from the standard input by the user  .
The programm   also   uses  the   math.h  library as  well asthe time.h and stdlib.h/stdio.h .
To change the parameters you have to change the source file and then re-compile the programm (see COMPILATION)

-Tournament Selection

	Tournament selection is a selection operator that     determines based 
	on a random number which of the 2 members of the  species   will    be 
	promoted and replace the other.Tournament selection favors  the fitter
	of the competing members 
	Reference [http://watchmaker.uncommons.org/manual/ch03s04.html]


Initial Parameters
--------------------------------------------------------------------------------
Name 	Value 		Description
--------------------------------------------------------------------------------
POPL 	10		Sets the population number 
GENS 	50		Sets the maximum number of generations
p_mut	0.1		Sets the possibility of mutation 
p_cross 0.3 		Sets the possibility of crossover
p_tourn 0.65		Sets the possibility of the fittest wining the tournament 
FITTEST LENGTH^2	Sets the FT parameter 
--------------------------------------------------------------------------------

--Return Values 
1 Evolution ended after reaching the max generations 
2 Evolution ended after reaching the Fittest threshold 

-Libraries
stdio
stdlib
time 
math.h 
