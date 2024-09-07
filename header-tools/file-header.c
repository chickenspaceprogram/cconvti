#include "file-header.h"


int write_file_header(FILE *fp)
{
    char *sig_1 = "**TI83F*";
    char *comment = "Created by cconvti, a .8x* file converter.";
    
    // checking for null
    if (fp == NULL)
    {
        return 3;
    }

    // writing signatures 1 and 2
    fputs(sig_1, fp);
    fputc(0x1A, fp);
    fputc(0x0A, fp);
    fputc(0x00, fp);

    // writing comment
    fputs(comment, fp);

    // writing data section length
    write_nulls(fp);

    return 0;
}

int edit_file_header(FILE *fp, unsigned short data_section_length)
{
    // checking for null
    if (fp == NULL)
    {
        return 3;
    }

    // going to start of data section length
    fseek(fp, 53, SEEK_SET);

    // writing LSB, then MSB because little endian
    fputc(0xFF & data_section_length, fp);
    fputc((0xFF00 & data_section_length) >> 8, fp);
    return 0;
}

/**
 * Writes two null bytes to the file at `fp`.
 */
void write_nulls(FILE *fp)
{
    fputc(0x00, fp);
    fputc(0x00, fp);
    return;
}