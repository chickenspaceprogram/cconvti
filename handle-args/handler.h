#ifndef HANDLER
#define HANDLER
#include <stdio.h>


/**
 * Contains all the information necessary to tokenize a file that is specific to that file.
 */
struct file
{
    char *filename;
    char *varname;
    char typeID;
};

/**
 * Contains a pointer pointing to an array of files, along with information that pertains to all the files.
 */
struct files_with_info
{
    struct file *all_files;
    int num_files;
    int ignore_warnings;
    int is_archived;
    int ignore_trailing_whitespace;

};

struct files_with_info get_files(int argc, char **argv);

#endif