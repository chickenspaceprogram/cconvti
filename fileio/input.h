#ifndef INPUT
#define INPUT
/**
 * Checks for errors (like rows of differing lengths) and stores the file at `filename` to the heap.
 * Returns a raw_csv struct.
 * Make sure to free() the array at locationptr!
 */
struct raw_csv *read_csv(char *filename);

/**
 * A struct containing a pointer to the data in a csv file, as well as the number of rows, columns, and the size of the largest entry (in bytes).
 */
struct raw_csv {
    char *locationptr;
    int num_rows;
    int num_cols;
    int max_entry_size;
};

/**
 * Reads the contents of a file into an array of characters and puts the contents onto the heap.
 * Returns a pointer to the array of characters.
 * Make sure to free() the array!
 */
char *read_text(char *filename);

#endif