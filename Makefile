CC = gcc
FLAGS = -Wall -Wextra -pedantic -std=c11

all: gameoflife.o libgol.so
	$(CC) $(FLAGS) -o gameoflife gameoflife.o -L. -lgol

libgol.so: gol.o
	$(CC) $(FLAGS) -shared gol.o -o libgol.so

gol.o: gol.c gol.h
	$(CC) $(FLAGS) -c gol.c -fPIC

gameoflife.o: gameoflife.c
	$(CC) $(FLAGS) -c gameoflife.c

clean:
	rm -rf gameoflife.o gol.o libgol.so gameoflife