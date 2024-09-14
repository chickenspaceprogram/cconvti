#include "handler.h"
#include "type-ID-defs.h"
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define NULLARRAY {0, 0, 0, 0, 0, 0, 0, 0, 0}

// need to make subfunction to return a filled file struct, since returning structs is a thing we can do.

struct files_with_info get_files(int argc, char **argv)
{
    struct file *files[argc / 2];
    
    struct files_with_info args_info = {
        .all_files = files,
        .ignore_trailing_whitespace = 0,
        .ignore_warnings = 0,
        .is_archived = 0,
        .num_files = 0
    };
    
    struct option long_options[] = {
        {"archive", no_argument, NULL, 'a'},//
        {"ignore-trailing-whitespace", no_argument, NULL, 't'},//
        {"ignore-warnings", no_argument, NULL, 'w'},//
        {"output", required_argument, NULL, 'o'},//
        {"var", required_argument, NULL, 'x'},
        {"complex-var", required_argument, NULL, 'z'},
        {"list", required_argument, NULL, 'l'},//
        {"complex-list", required_argument, NULL, 'c'},
        {"matrix", required_argument, NULL, 'm'},//
        {"yvar", required_argument, NULL, 'y'},
        {"string", required_argument, NULL, 's'},//
        {"prgm", required_argument, NULL, 'p'},//
        {"edit-locked-prgm", required_argument, NULL, 'e'},
        {"window-setting", required_argument, NULL, 'b'},
        {"table-setting", required_argument, NULL, 'd'},



        {NULL, 0, NULL, 0}

    };

    int ch;
    int current_char;
    int i;
    int current_file;
    int len_filename;

    while ((ch = getopt_long(argc, argv, "atwolmsp", long_options, NULL)) != -1)
    {
        switch (ch) 
        {
            case 'a':
                args_info.is_archived = 1;
                break;
            case 't':
                args_info.ignore_trailing_whitespace = 1;
                break;
            case 'w':
                args_info.ignore_warnings = 1;
                break;
            case 'o':
                len_filename = strlen(optarg) + 1;
                while ((optarg[i]) != 0)
                {
                    if (isalpha(optarg[i]) || (i > 0 && isnumber(optarg[i])))
                    {
                        args_info.all_files[current_file].varname
                    }
                }
                break;
            case 'x':
                break;
            case 'z':
                break;
            case 'l':
                break;
            case 'c':
                break;
            case 'm':
                break;
            case 'y':
                break;
            case 's':
                break;
            case 'p':
                break;
            case 'e':
                break;
            case 'b':
                break;
            case 'd':
                break;
        }
    }
}
