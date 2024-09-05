#ifndef CHECKSUM
#define CHECKSUM
#include <stdio.h>

/**
 * Adds a 2-byte-long checksum to the end of `fp`.
 * The checksum is equal to the sum of all bytes in the data section (the data itself, as well as the variable header).
 */
void add_checksum(FILE *fp);

#endif