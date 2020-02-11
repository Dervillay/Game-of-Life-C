all: gol.o gameoflife.c
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife gameoflife.c gol.o

gol.o: gol.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -c gol.c

clean:
	rm -rf gol.o gameoflife