#ifndef DATAHEADER
#define DATAHEADER

#include <stdio.h>

/**
 * Writes a data header to the file at `fp`.
 * The variable name is set to the first 8 elements at var_name.
 * If this succeeds, `0` will be returned.
 * If an error occurs, a nonzero value will be returned.
 * Note: This function initializes the length of the variable data to `00 00`.
 * To provide the length of the data section, you will need to call `edit_data_header`.
 */
int write_data_header(FILE *fp, char typeID, char *var_name, int is_archived);

/**
 * Edits the bytes of the data section containing the length of the variable data, changing them to represent the value of `variable_data_length`. 
 * The data section edited is the one starting at `data_section_start` located in file `fp`.
 * If this succeeds, `0` will be returned.
 * If an error occurs, a nonzero value will be returned.
 */
int edit_data_header(FILE *fp, unsigned short variable_data_length, long data_section_start);

#endif