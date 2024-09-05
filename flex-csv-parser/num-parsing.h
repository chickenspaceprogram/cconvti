#ifndef NUMPARSING
#define NUMPARSING

#include <stdio.h>

/*
`num_parsing` contains functions necessary to parse numbers from text format into the format used by TI-8x graphing calculators.
*/

/**
 * A real number, represented as it is on TI-8x calculators.
 * See https://merthsoft.com/linkguide/ti83+/vars.html for a good explanation.
 */
struct real_number {
    unsigned char flags;
    unsigned char exponent;
    unsigned char mantissa[7];
};

/**
 * Writes `number` to the file at `fp`.
 * `number` is written to `fp` using the format/byte ordering used on TI-8x calculators.
 */
void write_real_number(struct real_number number, FILE *fp);

/**
 * Parses the text string at `number` into a `real_number` struct.
 * If the number at `number` is the real or imaginary part of a complex number, set `is_complex` to a nonzero value.
 * Otherwise, set `is_complex` to zero.
 */
struct real_number parse_real_number(char *number, int is_complex);

#endif