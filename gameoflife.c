#include<stdio.h>
#include<stdlib.h>
#include"gol.h"

int main(int argc, char *argv[]){
  struct universe v; 
  char *infileName;
  char *outfileName;
  FILE *infile;
  FILE *outfile;
  int infileSpecified = 0;
  int outfileSpecified = 0;

  // Loop through args
  for (int i = 1; i < argc; i++) {

    // Enter switch statement only for args
    if (argv[i][0] == '-') {

      switch(argv[i][1]) {
        
        // Handle supplied input file
        case 'i':
          infileSpecified = 1; // Set flag
          infileName = argv[i+1]; // Get file name
          infile = fopen(infileName, "r"); // Open file

          // Check file has been opened successfully
          if (infile == NULL) {   
            fprintf(stderr, "Error: Could not open specified file\n"); 
            exit(-1);
          } 
          break;

        // Handle supplied output file
        case 'o':
          outfileSpecified = 1; // Set flag
          outfileName = argv[i+1]; // Get file name
          outfile = fopen(outfileName, "w"); // Open file

          // Check file has been opened successfully
          if (outfile == NULL) {   
            fprintf(stderr, "Error: Could not open specified file\n"); 
            exit(-1);
          } 
          break;
      }
    }
  }

  // If no file given, ask for it manually
  if (infileSpecified == 0) {
    // TODO
  }

  // If no output file specified, output to stdout
  if (outfileSpecified == 0) {
    outfile = stdout;
  }

  read_in_file(infile, &v);
  evolve(&v,will_be_alive_torus);
  write_out_file(outfile,&v);

  return 0;
}
