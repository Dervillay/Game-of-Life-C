#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"gol.h"

int main(int argc, char *argv[]) {
    struct universe u;
    char fileLine[513];

    read_in_file(stdin, &u);

    // Check for errors when reading in file
    if (u.cells[0][0] == -1) {
        fprintf(stderr, "Error: Supplied file was of invalid format\n");
        return 1;
    }

    return 0;
}

void read_in_file(FILE *infile, struct universe *u) {
    // Initialise list to hold max 512 characters (plus termination character)
    char line[513];
    // Initialise counter for rows in file
    int i = 0;

    // MUST ALLOCATE MEMORY PROPERLY!!!

    while (fscanf(infile, "%513[^\n]\n", line) != EOF) {
        for (int j = 0; j < sizeof(line)/24-1; j++) {
            // Allocate enough space for each column and row in the universe
            u -> cells[i][j] = (int) malloc(sizeof(int));

            /////
            /// THE ABOVE IS NOT ENOUGH, MUST BE ALLOCATED PROPERLY
            /////

            if (strncmp(&line[j], ".", 1) == 0) { // Detect .
                u -> cells[i][j] = 0;
                //printf("%d", u -> cells[i][j]);
            } else if (strncmp(&line[j], "*", 1) == 0) { // Detect *
                u -> cells[i][j] = 1;
                //printf("%d", u -> cells[i][j]);
            } else if (strncmp(&line[j], "\n", 1) == 0) { // Detect and skip spaces
                continue;
            } else { // Detect invalid characters and set first cell to -1 to represent this
                u -> cells[0][0] = -1;
            }
        }

        i += 1;
    }
}

void write_out_file(FILE *outfile, struct universe *u) {

}

int is_alive(struct universe *u, int column, int row) {
    return -1;
}

int will_be_alive(struct universe *u, int column, int row) {
    return -1;
}

int will_be_alive_torus(struct universe *u,  int column, int row) {
    return -1;
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)) {

}

void print_statistics(struct universe *u) {

}