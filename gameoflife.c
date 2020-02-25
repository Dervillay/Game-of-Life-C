#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"gol.h"

int main(int argc, char *argv[]){
  struct universe v; 
  char *infileName;
  char *outfileName;
  FILE *infile;
  FILE *outfile;
  int infileSpecified = 0;
  int outfileSpecified = 0;
  int numGenerations = 5;
  int printStats = 0;
  int useTorus = 0;

  // Loop through args
  for (int i = 1; i < argc; i++) {

    // Enter switch statement only for args
    if (argv[i][0] == '-') {

      if(strlen(argv[i]) != 2) {
        fprintf(stderr, "Error: %s is not a valid argument\n", argv[i]);
        exit(1);
      }

      if (i+1 == argc) {
        if (argv[i][1] == 'i' || argv[i][1] == 'o' || argv[i][1] == 'g') {
          fprintf(stderr, "Error: No input given for arg -%c\n", argv[i][1]);
          exit(1);
        }
      }

      switch(argv[i][1]) {

        // Handle supplied input file
        case 'i':
          infileSpecified = 1; // Set flag
          infileName = argv[i+1]; // Get file name
          infile = fopen(infileName, "r"); // Open file

          // Check file has been opened successfully
          if (infile == NULL) {   
            fprintf(stderr, "Error: Could not open specified input file, please check that one was provided.\n"); 
            exit(-1);
          } 
          break;

        // Handle supplied output file
        case 'o':
          // Check output file has been provided
          if (argv[i+1][0] == '-') {
            fprintf(stderr, "Error: No output file was specified.\n");
            exit(1);
          }

          outfileSpecified = 1; // Set flag
          outfileName = argv[i+1]; // Get file name
          outfile = fopen(outfileName, "w"); // Open file

          // Check file has been opened successfully
          if (outfile == NULL) {   
            fprintf(stderr, "Error: Could not open specified output file, please check that one was provided.\n"); 
            exit(-1);
          } 
          break;

        // Handle specified number of generations
        case 'g':
          // Check supplied argument is a number
          for (int j = 0; argv[i+1][j] != '\0'; j++) {
            if (!isdigit(argv[i+1][j])) {
              printf("%c\n", argv[i+1][j]);
              fprintf(stderr, "Error: -g argument received an invalid value, please check the value supplied is an integer.\n");
              exit(1);
            }
          }

          numGenerations = atoi(argv[i+1]);
          break;

        // Handle printing statistics
        case 's':
          printStats = 1;
          break;

        // Switch to torus topology rule
        case 't':
          useTorus = 1;
          break;

        // Handle unrecognised arguments
        default:
          fprintf(stderr, "Error: %s is not a valid argument\n", argv[i]);
          exit(1);
      }

    // Handle unrecognised args that aren't in -arg format
    } else if (argv[i-1][0] != '-' || argv[i-1][1] == 's' || 
               argv[i-1][1] == 't') {
        fprintf(stderr, "Error: %s is not a valid argument\n", argv[i]);
        exit(1);
    }
  }

  // If no input file given, take input manually
  if (!infileSpecified) {
    infile = stdin;
  }

  // Read in supplied file
  read_in_file(infile, &v);

  // Close infile
  fclose(infile);

  // Call evolve numGenerations times
  for (int j = 0; j < numGenerations; j++) {
    if (useTorus) {
      evolve(&v, will_be_alive_torus);
    } else {
      evolve(&v, will_be_alive);
    }
  }

  // If no output file specified, output to stdout
  if (!outfileSpecified) {
    outfile = stdout;

    // If no input, add linebreak for neatness
    if (!infileSpecified) {
      printf("\n");
    }
  }

  // Write result to outfile
  write_out_file(outfile, &v);

  // Print statistics if asked for
  if (printStats) {
    print_statistics(&v);
  }

  // Close outfile
  fclose(outfile);

  return 0;
}
