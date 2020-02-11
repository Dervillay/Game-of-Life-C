all: gol.c func.o
	gcc -Wall -o gameoflife main.o func.o

func.o: gol.c gol.h
	gcc -Wall -c func.c

main.o: gol.c
	gcc -Wall -c gol.c

clean:
	rm -rf gameoflife gol.o

