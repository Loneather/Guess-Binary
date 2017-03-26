CC=gcc
CFLAGS=-Wall
Math=-lm
dbg = -g

../bin/guessga : guessga.o functions.o genoperators.o
	$(CC) $(CFLAGS) genoperators.o guessga.o functions.o -o ../bin/guessga $(Math) $(dbg)

guessga.o : guessga.c
	$(CC) $(CFLAGS) -c guessga.c $(Math) $(dbg)

functions.o : functions.c
	$(CC) $(CFLAGS) -c functions.c $(Math) $(dbg)
genoperators.o : genoperators.c
	$(CC) $(CFLAGS) -c genoperators.c $(Math) $(dbg)




.PHONY: clean

clean:
	rm -f guessga.o functions.o genoperators.o 
