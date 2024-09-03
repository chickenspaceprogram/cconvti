#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "input.h"

#define STARTING_BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

/**
 * Uses realloc() to give a char array twice the space that it currently has.
 * Requires both a pointer to the array as well as the current amount of space the array has.
 */
char *allocate_space(char *variable, int current_size, int desired_size) 
{
    variable = realloc(variable, desired_size);
    if (desired_size > current_size) 
    {
        for (int i = current_size; i < desired_size; ++i) 
        {
            variable[i] = 0;
        }
    }
    return variable;
}


/**
 * - Reads a CSV into memory
 * - Replaces newlines with commas
 * - Returns a struct with:
 *      - a pointer to the CSV
 *      - the number of rows
 *      - the number of columns
 *      - the number of characters in the longest entry
 * this function is massive and needs refactoring but a CSV parser is literally on the bottom of the things I want to do in this project.
 */
struct RawCSV read_csv(char *filename) 
{
    char current_char;
    int current_char_position = 0;
    int file_size = STARTING_BUFFER_SIZE;
    int num_cols = 0;
    int on_first_row = TRUE;
    int num_rows = 0;
    int char_is_carriage_return = FALSE;
    int elements_in_current_row = 0;
    int max_entry_size = 0;
    int current_entry_size = 0;
    int i = 0;

    // opening file, making sure that it exists.
    FILE *fileptr = fopen(filename, "r");
    if (fileptr == NULL) 
    {
        fprintf(stderr, "Could not find the file at `%s`.\ncconvti exiting...\n", filename);
        exit(1);
    }

    // ensuring that the first character of the file isn't an EOF
    current_char = getc(fileptr);
    if (current_char == EOF) 
    {
        fprintf(stderr, "The file at `%s` is empty.\ncconvti exiting...\n", filename);
        fclose(fileptr);
        exit(1);
    }

    // creating the buffer into which the file will be read
    char *buffer = malloc(STARTING_BUFFER_SIZE);

    /* reading each character from the file, one by one
    This is a do-while loop to separate the logic for checking for an empty file from the rest of the logic.
    Best not to have another redundant if check in the for loop. */
    do 
    {
        // if we need more space, allocate more
        if (current_char_position == file_size) 
        {
            buffer = allocate_space(buffer, file_size, file_size * 2);
            file_size *= 2;
        }

        // make sure to debug this monster of a swtich statement.
        switch (current_char)
        {
            case '\r':
                char_is_carriage_return = TRUE;
                break;
            case '\n':
                ++num_rows;
                if (elements_in_current_row != 0) 
                {
                    ++elements_in_current_row;
                }
                if (on_first_row) 
                {
                    on_first_row = FALSE;
                    num_cols = elements_in_current_row;
                } 
                else if (elements_in_current_row != num_cols) 
                {
                    fclose(fileptr);
                    fprintf(stderr, "Uneven row in file `%s`: Row %d is %d elements long, while other rows are %d elements long.\ncconvti exiting...\n", filename, num_rows, elements_in_current_row, num_cols);
                    exit(1);
                }
                elements_in_current_row = 0;
                buffer[current_char_position] = ',';
                ++current_char_position;
                char_is_carriage_return = FALSE;
                break;
            case ',':
                ++elements_in_current_row;
                if (current_entry_size > max_entry_size) {
                    max_entry_size = current_entry_size;
                }
                current_entry_size = -1;
            default:
                char_is_carriage_return = FALSE;
                buffer[current_char_position] = current_char;
                ++current_char_position;
                ++current_entry_size;
        }
        current_char = getc(fileptr);
        if (char_is_carriage_return && current_char != '\n') 
        {
            fprintf(stderr, "Carriage return (\\r) found without corresponding newline (\\n) in file `%s`.\ncconvti exiting...\n", filename);
            fclose(fileptr);
            exit(1);
        }
    } while (current_char != EOF);

    // closing file and making buffer as small as possible
    fclose(fileptr);
    buffer = allocate_space(buffer, file_size, ++current_char_position);

    // ensuring rows are even
    if (elements_in_current_row != 0) 
    {
        ++elements_in_current_row;
    }
    if (on_first_row) 
    {
        num_cols = elements_in_current_row;
    }
    if (elements_in_current_row != num_cols) 
    {
        fclose(fileptr);
        fprintf(stderr, "Uneven row in file `%s`: Row %d is %d elements long, while other rows are %d elements long.\ncconvti exiting...\n", filename, ++num_rows, elements_in_current_row, num_cols);
        exit(1);
    }

    // this is a bad way to do this. implement a hashmap, regex, or something that sucks less in future
    while (buffer[i] != 0) 
    {
        switch(buffer[i]) 
        {
            case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0': case 'e': case 'E': case '+': case '-': case ',': case '.':
                ++i;
                break;
            default:
                fprintf(stderr, "Found a non-allowed character `%c` in file `%s`.\n", buffer[i], filename);
                exit(1);
        }
    }

    struct RawCSV return_struct = {buffer, ++num_rows, num_cols, max_entry_size};
    return return_struct;

}