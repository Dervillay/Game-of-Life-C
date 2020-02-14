#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u) {
    char line[514]; // Initialise list to hold max 512 characters (\r and \n characters)
    int array_size = 1; // Set abritrary starting size for input
    int i = 0; // Track num of rows in file
    int lineLen = 0; // Track length of each row (num of columns)
    int prevLineLen = -1; // Track length of previous row's length
    int numAlive = 0; // Track number of alive cells in provided grid

    // Check infile is not blank
    if (infile != stdin) {
        fseek(infile, 0, SEEK_END);
        int fileSize = ftell(infile);

        if (fileSize < 1) {
            fprintf(stderr, "Error: Supplied file is empty\n");
            exit(1);
        }

        // Return file position indicator back to start
        fseek(infile, 0, SEEK_SET);
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
        for(int l = 0; l <= (int) strlen(line); l++) {
            if(strncmp(&line[l], "\n", 1) == 0) {
                break;    	
            }
            lineLen = l;
	    }

        // Set prevLineLen on first loop
        if (prevLineLen == -1) {
            prevLineLen = lineLen;
        }

        // Allocate enough space in cells[i] for each char in the current line
        if ((u -> cells[i] = realloc(u -> cells[i], lineLen * sizeof(char*))) == NULL) {
            fprintf(stderr, "Error: Ran out of memory\n");
            free(u); // Free u from memory
            exit(1);
        }

        // Iterate through each item of the row and store chars in universe
        for (int j = 0; j < (int) strlen(line); j++) {
            if (lineLen != prevLineLen) { // Detect inconsistent line lengths and print error
                fprintf(stderr, "Error: File supplied contains inconsistent row lengths\n");
                exit(1);
            } else if (strncmp(&line[j], ".", 1) == 0) { // Detect . char
                u -> cells[i][j] = line[j];
            } else if (strncmp(&line[j], "*", 1) == 0) { // Detect * char and increment numAlive
                u -> cells[i][j] = line[j];
                numAlive += 1;
            } else if (strncmp(&line[j], "\n", 1) == 0) { // Detect and skip newlines
                continue;
            } else { // Detect invalid characters and print error
                fprintf(stderr, "Error: File supplied contains invalid characters\n");
                exit(1);
            }
        }

        // Increment number of rows and update prevLineLen
        i += 1;
        prevLineLen = lineLen;
    }

    // Close file after reading
    fclose(infile);

    // Set number of rows and columns in u
    u -> rows = i;
    u -> columns = lineLen;

    // Set number of alive cells in u and initialise generation & prevAvgAlive to 0
    u -> numAlive = numAlive;
    u -> generation = 0;
    u -> prevAvgAlive = 0;
}

void write_out_file(FILE *outfile, struct universe *u) {
    // Iterate through all of u and print contents
    for (int i = 0; i < u -> rows; i++) {
        for (int j = 0; j < u -> columns; j++) {
            fprintf(outfile, "%c", u -> cells[i][j]);
        }
        fprintf(outfile, "\n");
    }
}

int is_alive(struct universe *u, int column, int row) {
    // Handle invalid indices
    if (column < 0 || column >= u -> columns) {
        fprintf(stderr, "Error: Invalid index given. Only columns 0 to %d exist\n", (u -> columns)-1);
        exit(1);
    } else if (row < 0 || row >= u -> rows) {
        fprintf(stderr, "Error: Invalid index given. Only rows 0 to %d exist\n", (u -> rows)-1);
        exit(1);
    }

    // Handle when cell is alive
    if (strncmp(&(u -> cells[row][column]), "*", 1) == 0) {
        return 1;
    // Handle when cell is dead
    } else {
        return 0;
    }
}

int will_be_alive(struct universe *u, int column, int row) {
    // Handle invalid indices
    if (column < 0 || column >= u -> columns) {
        fprintf(stderr, "Error: Invalid index given. Only columns 0 to %d exist\n", (u -> columns)-1);
        exit(1);
    } else if (row < 0 || row >= u -> rows) {
        fprintf(stderr, "Error: Invalid index given. Only rows 0 to %d exist\n", (u -> rows)-1);
        exit(1);
    }

    // Initialise number of live neighbours to 0
    int liveNeighbours = 0;

    // Find number of live neighbours

    // Cell is top left
    if (column == 0 && row == 0) {
        liveNeighbours += is_alive(u, column+1, row);
        liveNeighbours += is_alive(u, column+1, row+1);
        liveNeighbours += is_alive(u, column, row+1);

    // Cell is bottom left
    } else if (column == 0 && row == u -> rows-1) {
        liveNeighbours += is_alive(u, column+1, row);
        liveNeighbours += is_alive(u, column+1, row-1);
        liveNeighbours += is_alive(u, column, row-1);

    // Cell is bottom right
    } else if (column == u -> columns-1 && row == u -> rows-1) {
        liveNeighbours += is_alive(u, column, row-1);
        liveNeighbours += is_alive(u, column-1, row-1);
        liveNeighbours += is_alive(u, column-1, row);

    // Cell is top right
    } else if (column == u -> columns-1 && row == 0) {
        liveNeighbours += is_alive(u, column, row+1);
        liveNeighbours += is_alive(u, column-1, row+1);
        liveNeighbours += is_alive(u, column-1, row);

    // Cell lies along top edge
    } else if (row == 0) {
        liveNeighbours += is_alive(u, column+1, row);
        liveNeighbours += is_alive(u, column+1, row+1);
        liveNeighbours += is_alive(u, column, row+1);
        liveNeighbours += is_alive(u, column-1, row+1);
        liveNeighbours += is_alive(u, column-1, row);

    // Cell lies along left edge
    } else if (column == 0) {
        liveNeighbours += is_alive(u, column, row+1);
        liveNeighbours += is_alive(u, column+1, row+1);
        liveNeighbours += is_alive(u, column+1, row);
        liveNeighbours += is_alive(u, column+1, row-1);
        liveNeighbours += is_alive(u, column, row-1);

    // Cell lies along bottom edge
    } else if (row == u -> rows-1) {
        liveNeighbours += is_alive(u, column+1, row);
        liveNeighbours += is_alive(u, column+1, row-1);
        liveNeighbours += is_alive(u, column, row-1);
        liveNeighbours += is_alive(u, column-1, row-1);
        liveNeighbours += is_alive(u, column-1, row);

    // Cell lies along right edge
    } else if (column == u -> columns-1) {
        liveNeighbours += is_alive(u, column, row+1);
        liveNeighbours += is_alive(u, column-1, row+1);
        liveNeighbours += is_alive(u, column-1, row);
        liveNeighbours += is_alive(u, column-1, row-1);
        liveNeighbours += is_alive(u, column, row-1);

    // Cell lies elsewhere
    } else {
        liveNeighbours += is_alive(u, column+1, row);
        liveNeighbours += is_alive(u, column+1, row-1);
        liveNeighbours += is_alive(u, column, row-1);
        liveNeighbours += is_alive(u, column-1, row-1);
        liveNeighbours += is_alive(u, column-1, row);
        liveNeighbours += is_alive(u, column-1, row+1);
        liveNeighbours += is_alive(u, column, row+1);
        liveNeighbours += is_alive(u, column+1, row+1);
    }

    // Cell is currently alive
    if (is_alive(u, column, row)) {
        if (liveNeighbours == 2 || liveNeighbours == 3) {
            return 1;
        } else {
            return 0;
        }
    // Cell is currently dead
    } else {
        if (liveNeighbours == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int will_be_alive_torus(struct universe *u,  int column, int row) {
    // Store number of columns and rows
    int columns = u -> columns;
    int rows = u -> rows;

    // Set initial pre column and row values
    int preColumn = column;
    int preRow = row;

    // Initialise number of live neighbours to 0
    int liveNeighbours = 0;

    // Handle invalid indices
    if (column < 0 || column >= columns) {
        fprintf(stderr, "Error: Invalid index given. Only columns 0 to %d exist\n", columns-1);
        exit(1);
    } else if (row < 0 || row >= rows) {
        fprintf(stderr, "Error: Invalid index given. Only rows 0 to %d exist\n", rows-1);
        exit(1);
    }

    // Handle if columns/rows would go negative
    if (column == 0) {
        preColumn = columns;
    }
    if (row == 0) {
        preRow = rows;
    }

    // Find number of live neighbours
    liveNeighbours += is_alive(u, (column+1) % columns, row);
    liveNeighbours += is_alive(u, (column+1) % columns, preRow-1);
    liveNeighbours += is_alive(u, column, preRow-1);
    liveNeighbours += is_alive(u, preColumn-1, preRow-1);
    liveNeighbours += is_alive(u, preColumn-1, row);
    liveNeighbours += is_alive(u, preColumn-1, (row+1) % rows);
    liveNeighbours += is_alive(u, column, (row+1) % rows);
    liveNeighbours += is_alive(u, (column+1) % columns, (row+1) % rows);

    // Cell is currently alive
    if (is_alive(u, column, row)) {
        if (liveNeighbours == 2 || liveNeighbours == 3) {
            return 1;
        } else {
            return 0;
        }
    // Cell is currently dead
    } else {
        if (liveNeighbours == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)) {
    // Get column & row lengths and initialise 2D array to store next generation
    int columns = u -> columns;
    int rows = u -> rows;
    char cells[rows][columns];

    // Initialise number of live cells to 0
    int numAlive = 0;

    // Calculate next generation and store in cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (rule(u, j, i) == 1) {
                cells[i][j] = '*';
                numAlive += 1;
            } else if (rule(u, j, i) == 0) {
                cells[i][j] = '.';
            } else {
                fprintf(stderr, "Error: Given rule returned non-binary value\n");
                exit(1);
            }
        }
    }

    // Replace u -> cells with cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            u -> cells[i][j] = cells[i][j];
        }
    }

    // Update generation, numAlive and prevAvgAlive
    u -> generation += 1;
    u -> numAlive = numAlive;
    u -> prevAvgAlive = (((u -> prevAvgAlive * (u -> generation-1)) + numAlive) / (u -> generation));
}

void print_statistics(struct universe *u) {
    // Print percentage of cells currently alive
    fprintf(stdout, "%.3f%% of cells currently alive\n", (float) (u -> numAlive) / ((u -> rows) * (u -> columns)));

    // Print percentage of cells alive on average across all generations
    fprintf(stdout, "%.3f%% of cells alive on average\n", (float) (u -> prevAvgAlive) / ((u -> rows) * (u -> columns)));
}
