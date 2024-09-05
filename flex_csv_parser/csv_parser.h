#ifndef CSV_PARSER
#define CSV_PARSER

#include <stdio.h>
/*
Reads and parses CSV into the format used by TI-BASIC.
 - Takes a pointer to the input file and the output file as arguments, as well as a boolean determining whether the CSV contains complex values.
 - Returns status. If the returned value is nonzero, an error occurred.
*/
int read_csv(FILE *input_fileptr, FILE *output_fileptr, int csv_is_complex);

#endif