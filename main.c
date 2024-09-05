#include <stdio.h>
#include <stdlib.h>
#include "flex_csv_parser/csv_parser.h"

int main(int argc, char *argv[]) 
{
    // garbage arg handling, don't worry, this will be made to suck less in future
    // first arg is input, second is output
    if (argc == 3) 
    {
        FILE *input_fp = fopen(argv[1], "r");
        FILE *output_fp = fopen(argv[2], "wb");
        int csv_parser_status = read_csv(input_fp, output_fp, 0); 
        if (csv_parser_status) 
        {
            printf("cconvti exiting...\n");
            return 1;
        }
    else
    {
        fprintf(stderr, "Incorrect number of arguments.\ncconvti exiting...\n");
        return 1;
    }
    return 0;
}