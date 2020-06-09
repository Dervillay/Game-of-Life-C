# Game-of-Life-C
A simulator for John Conway's 'Game of Life' written in C.
For those unfamiliar, you can read about it [here](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## Input
The program expects a `.txt` file as input, consisting of `.` to represent empty spaces and `*` to represent live cells.
Each line should be of the same length and terminated with a newline character.

If the input deviates from this, an informative error will be provided.

The file `glider.txt` has been given as an example:
```
....................\n
....................\n
....................\n
....................\n
...*................\n
....*...............\n
..***...............\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n
....................\n

```

## Running the program
- Clone and `cd` into this repository
- Type `make` to run the Makefile and prepare the files
- To run an input file `input.txt` with default settings, type `./gameoflife -i input.txt`
- For more customisability, use the arguments below

## Arguments
- `-i input_file.txt` takes `input_file.txt` as input. If not specified, the program will expect the user to provide an input line by line instead
- `-o output_file.txt` will write the output to `output_file.txt`, or to stdout if not specified 
- `-g num_generations` will run the input through `num_generations` iterations before returning an output. If not specified this will default to 5
- `-s` will print the percentage of total cells alive on average across generations along with the percentage of cells alive in the final generation
- `-t` will treat the grid as if it were a torus, i.e. that each cell along a border is neighbouring the cells on the opposite border (imagine the way Pac-Man works). If not specified, the grid is treated as if there is an additional layer of dead cells surrounding it




