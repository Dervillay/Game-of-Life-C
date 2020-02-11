CC = gcc
FLAGS = -Wall -Wextra -pedantic -std=c11

all: gameoflife.c libgol.so
	$(CC) $(FLAGS) -o gameoflife gameoflife.c -L. -lgol

libgol.so: gol.o
	$(CC) $(FLAGS) -shared gol.o -o libgol.so

gol.o: gol.c gol.h
	$(CC) $(FLAGS) -c gol.c -fPIC

clean:
	rm -rf gol.o libgol.so gameoflife