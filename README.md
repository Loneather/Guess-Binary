
## Introduction
This programm guesses a binary string that the user inputs using evolutionary computation
methods


## Motivation
This project was developed as part of a Programming Course.I am using it exercise programming various genetic programming techniques.I would be glad if you contributed .

## Installation

While on main folder run :

	$make
	$make clean
## Execution

On the main folder run :

	$./guessga -np -s [SEED]
	-np :If selected doesn't print the results for each generation
	-s OPTIONAL : it determines the seed that the random function will use .So that you can reproduce your results

## Genetic Operators
Currently tournament selction ,roulette wheel selection ,mutation ,single point crossover .The paramaters for the genetic operators are defined in the source code .
