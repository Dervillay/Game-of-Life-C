#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"gol.h"

int main(int argc, char *argv[]) {
    struct universe u;
    char fileLine[513];

    read_in_file(stdin, &u);

    write_out_file(stdout, &u);

    return 0;
}

void read_in_file(FILE *infile, struct universe *u) {
    // Initialise list to hold max 512 characters (plus termination character)
    char line[514];
    int array_size = 1; // Set abritrary starting size for input
    int i = 0; // Track num of rows in file
    int lineLen = 0; // Track length of each row's length (num of columns)
    int prevLineLen = -1; // Track length of previous row's length

    // Check infile is not blank
    if (infile != NULL) {
        fseek(infile, 0, SEEK_END);
        int fileSize = ftell(infile);

        if (fileSize < 1) {
            fprintf(stderr, "Error: Supplied file is empty\n");
            exit(1);
        }

        // Return file position indicator back to start
        fseek(infile, 0, SEEK_SET);
    } else {
        fprintf(stderr, "Error: Supplied file cannot be NULL\n");
        exit(1);
    }

    // Allocate initial array_size columns in universe
    if ((u -> cells = malloc(array_size * sizeof(char*))) == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for cells\n");
        exit(1);
    }

    while (fscanf(infile, "%s", line) != EOF) {
        // Reallocate more memory if neccesary
        if (i >= array_size) {
            char **newp;
            array_size += 1;
            newp = realloc(u -> cells, array_size * sizeof(char*));

            // Check realloc was successful
            if (newp == NULL) {
                fprintf(stderr, "Error: Ran out of memory\n");
                exit(1);
            }
            // Assign new pointer to u -> cells
            u -> cells = newp;
        }

        // Calculate and store length of current line
        for(i = 0; i <= strlen(line); i++) {
            if(strncmp(&line[i], "\n", 1) == 0) {
                break;    	
            }
            lineLen = i;
	    }

        // Set prevLineLen on first loop
        if (prevLineLen == -1) {
            prevLineLen = lineLen;
        }

        // Allocate enough space in cells[i] for each char in the current line
        if ((u -> cells[i] = realloc(u -> cells, lineLen * sizeof(char*))) == NULL) {
            fprintf(stderr, "Error: Ran out of memory\n");
            exit(1);
            free(u); // Free u from memory
        }

        // Iterate through each item of the row and store chars in universe
        for (int j = 0; j < strlen(line); j++) {
            
            if (lineLen != prevLineLen) { // Detect inconsistent line lengths and print error
                fprintf(stderr, "Error: File supplied contains inconsistent row lengths\n");
                exit(1);
            } else if (strncmp(&line[j], ".", 1) == 0) { // Detect . char
                u -> cells[i][j] = line[j];
                printf("%c", u -> cells[i][j]);
            } else if (strncmp(&line[j], "*", 1) == 0) { // Detect * char
                u -> cells[i][j] = line[j];
                printf("%c", u -> cells[i][j]);
            } else if (strncmp(&line[j], "\n", 1) == 0) { // Detect and skip newlines
                continue;
            } else { // Detect invalid characters and print error
                fprintf(stderr, "Error: File supplied contains invalid characters\n");
                exit(1);
            }
        }
        printf("\n");

        i += 1;
        prevLineLen = lineLen;
    }

    // Close file after reading
    fclose(infile);
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