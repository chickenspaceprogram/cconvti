#ifndef CSV_PARSER
#define CSV_PARSER

#include <stdio.h>

/**
 * A struct containing information about the CSV that was parsed.
 * - `num_rows` - the number of rows in the CSV
 * - `num_cols` - the number of columns in the CSV
 * - `status` - equal to 0 if the CSV was parsed successfully, nonzero if there was an error.
 * `status == 2` - input file did not exist
 * `status == 3` - pointer to output file was null
 * `status == 4` - some sort of formatting error occurred while parsing the CSV (user did not format values correctly)
 */
struct csv_info {
    int status;
    int num_rows;
    int num_cols;
};

/**
 * Reads and parses CSV into the format used by TI-BASIC.
 * - `inputfp` is a pointer to the input file (the CSV that is being read)
 * - `outputfp` is a pointer to the output file
 * Returns a `csv_info` containing a status code and the size of the CSV that was processed.
 */
struct csv_info read_csv(FILE *inputfp, FILE *outputfp, int csv_is_complex);

#endif