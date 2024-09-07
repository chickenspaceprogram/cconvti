#ifndef FILEHEADER
#define FILEHEADER
#include <stdio.h>

/**
 * Writes a file header to the file at `fp`.
 * If this succeeds, `0` will be returned.
 * If an error occurs, a nonzero value will be returned.
 * Note: This function initializes the length of the data section to `00 00`.
 * To provide the length of the data section, you will need to call `edit_file_header`.
 */
int write_file_header(FILE *fp);

/**
 * Edits the bytes in the file header storing the length of the data header.
 * `fp` is a pointer to the file.
 * `data_section_length` is the length of the entire data section, including data headers, in bytes.
 * If this succeeds, `0` will be returned.
 * If an error occurs, a nonzero value will be returned.
 */
int edit_file_header(FILE *fp, unsigned short data_section_length); 

#endif