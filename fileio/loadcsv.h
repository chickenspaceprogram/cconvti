#ifndef INPUT
#define INPUT
/**
 * Checks for errors (like rows of differing lengths) and stores the file at `filename` to the heap.
 * Returns a raw_csv struct.
 * Make sure to free() the array at locationptr!
 */
struct RawCSV read_csv(char *filename);

/**
 * A struct containing a pointer to the data in a csv file, as well as the number of rows, columns, and the size of the largest entry (in bytes).
 */
struct RawCSV 
{
    char *locationptr;
    int num_rows;
    int num_cols;
    int max_entry_size;
};

#endif