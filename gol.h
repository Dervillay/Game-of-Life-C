struct universe {
/*Put some appropriate things here*/
    char **cells; // 2D array of cells and their current states
    int rows; // Number of rows
    int columns; // Number of columns
    int generation; // Number indicating which generation the universe is (beginning at 0)
    int numAlive; // Number of alive cells in current generation
    int prevAvgAlive; // Average number of cells alive across all previous generations
};

/*Do not modify the next seven lines*/
void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
int will_be_alive_torus(struct universe *u,  int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);
/*You can modify after this line again*/

