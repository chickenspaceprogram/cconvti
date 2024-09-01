#include <stdio.h>
#include <stdlib.h>
#define STARTING_BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0


struct raw_csv *read_csv(char *filename) {
    char current_char;
    int current_char_position = 0;
    int file_size = STARTING_BUFFER_SIZE;
    int num_cols = 0;
    int on_first_row = TRUE;
    int elements_in_current_row = 0;
    int num_rows = 0;
    int reached_EOF = FALSE;

    FILE *fileptr = fopen(filename, "r");
    if (fileptr == NULL) {
        fprintf(stderr, "Could not find the file at `%s`.\nExiting...\n", filename);
        exit(1);
    }

    char current_char = getc(fileptr);
    if (current_char == EOF) {
        fprintf(stderr, "The file at `%s` is empty.\nExiting...\n", filename);
        fclose(fileptr);
        exit(1);
    }

    char *buffer = malloc(STARTING_BUFFER_SIZE);
    do {
        if (current_char_position == file_size) {
            buffer = allocate_more_space(buffer, file_size);
            file_size *= 2;
        }
        buffer[current_char_position] = current_char;
        switch (current_char) {
            case EOF:
                reached_EOF = TRUE;
            case '\n':
                ++elements_in_current_row;
                if (on_first_row) {
                    num_cols = elements_in_current_row;
                    on_first_row = FALSE;
                } else if (num_cols != elements_in_current_row) {

                }
                buffer[current_char_position] = ',';
                break;
            case ',':
                ++elements_in_current_row;
            default:
                buffer[current_char_position] = current_char;
        }
        current_char = getc(fileptr);
        ++current_char_position;
    } while (current_char != EOF);
}

/**
 * Uses realloc() to give a char array twice the space that it currently has.
 * Requires both a pointer to the array as well as the current amount of space the array has.
 */
char *allocate_more_space(char *variable, int current_space) {
    variable = realloc(variable, current_space * 2);
    for (int i = current_space; i < current_space * 2; ++i) {
        variable[i] = 0;
    }
    return variable;
}