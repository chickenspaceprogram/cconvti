#include "data-header.h"

// these comments are unintelligible, sorry lol


int write_data_header(FILE *fp, char typeID, char *var_name, int is_archived)
{
    // writing 0D 00 bytes
    fputc(0x0D, fp);
    fputc(0x00, fp);

    // writing first var data length
    write_nulls(fp);

    // writing typeID
    fputc(typeID, fp);

    // writing variable name
    for (int i = 0; i < 8; ++i)
    {
        fputc(var_name[i], fp);
    }

    // setting version byte (always set to null)
    fputc(0x00, fp);

    // setting the byte that determines if the variable is archived
    if (is_archived)
    {
        fputc(0x80, fp);
    }
    else
    {
        fputc(0x00, fp);
    }

    // writing second var data length
    write_nulls(fp);

    return 0; // no current code for error checking, but that will be implemented in future
}



int edit_data_header(FILE *fp, unsigned short variable_data_length, long data_section_start)
{
    if (fp == NULL)
    {
        return 3;
    }

    // going to first variable data length bytes and writing the bytes there
    fseek(fp, data_section_start + 2, SEEK_SET);
    fputc(0xFF & variable_data_length, fp);
    fputc((0xFF00 & variable_data_length) >> 8, fp);

    // going to first variable data length bytes and writing the bytes there
    fseek(fp, data_section_start + 15, SEEK_SET);
    fputc(0xFF & variable_data_length, fp);
    fputc((0xFF00 & variable_data_length) >> 8, fp);

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