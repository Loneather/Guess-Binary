CC=gcc
CFLAGS=-Wall
Math=-lm
dbg = -g3

guessga : guessga.o functions.o
	$(CC) $(CFLAGS) guessga.o functions.o -o ./bin/guessga $(Math) $(dbg)

guessga.o : ./src/guessga.c
	$(CC) $(CFLAGS) -c ./src/guessga.c -o guessga.o $(Math) $(dbg)

functions.o : ./src/functions.c
	$(CC) $(CFLAGS) -c ./src/functions.c -o functions.o $(Math) $(dbg)
	



.PHONY: clean

clean:
	rm -f guessga.o functions.o
