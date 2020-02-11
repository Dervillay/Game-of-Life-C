CC = gcc
FLAGS = -Wall -Wextra -pedantic -std=c11

all: gameoflife.c
	export LD_LIBRARY_PATH=`pwd`
	$(CC) $(FLAGS) -o gameoflife gameoflife.c -L. -lgol

libgol.so: gol.o
	$(CC) $(FLAGS) -shared gol.o -o libgol.so

gol.o: gol.c gol.h
	$(CC) $(FLAGS) -c gol.c -fPIC

clean:
	rm -rf gol.o gameoflife