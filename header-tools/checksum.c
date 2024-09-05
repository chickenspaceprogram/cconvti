#include "checksum.h"

void add_checksum(FILE *fp)
{
    fseek(fp, 55, SEEK_SET);
    int current_char = fgetc(fp);
    unsigned short checksum = 0;
    while (current_char != EOF)
    {
        checksum += (unsigned char) current_char;
        current_char = fgetc(fp);
    }
    fseek(fp, 0, SEEK_END);

    // the z80 is little-endian
    fputc(checksum & 0xFF, fp);
    fputc((checksum & 0xFF00) >> 8, fp);
}