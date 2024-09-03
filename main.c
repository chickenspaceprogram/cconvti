#include <stdio.h>
#include <stdlib.h>
#include "fileio/input.h"

int main(int argc, char *argv[]) 
{
    // garbage arg handling, don't worry, this will be made to suck less in future
    struct RawCSV csv = read_csv(argv[1]);
    printf("CSV elements: %s\nNumber of rows: %d\nNumber of columns: %d\nNumber of characters in largest entry: %d\n", csv.locationptr, csv.num_rows, csv.num_cols, csv.max_entry_size);
    free(csv.locationptr);
    return 0;
}