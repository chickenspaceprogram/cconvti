CSV_ENTRY   -?[0-9]+"."?[0-9]*([eE][+-][0-9]+)?

%{
    #include "csv_parser.h"
    #include "num_parsing.h"

    // i know globals kinda suck, don't bully me
    int num_rows = 0;
    int num_cols = 0;
    int entries_in_current_row = 0;
    int is_complex;
    int error_counter = 0;

%}

%%

,{CSV_ENTRY}   {
        write_real_number(parse_real_number(yytext + 1), yyout);
        ++entries_in_current_row;
}

^{CSV_ENTRY}    {
        if (num_rows == 0) 
        {
            num_cols = entries_in_current_row;
        } 
        else if (entries_in_current_row != num_cols) 
        {
            fprintf(stderr, "Uneven rows: Row %d is %d entries long, while the first row is %d entries long.\n", num_rows, entries_in_current_row, num_cols);
            ++error_counter;
        }
        write_real_number(parse_real_number(yytext), yyout);
        ++num_rows;
        entries_in_current_row = 1;
    }
\n  ;

.   {
        fprintf(stderr, "Invalid entry `%s`.\n", yytext);
        ++error_counter;
    }
%%

/*
Reads and parses CSV into the format used by TI-BASIC.
Returns status. If the returned value is nonzero, an error occurred.
*/
struct csv_info read_csv(FILE *inputfp, FILE *outputfp, int csv_is_complex)
{
    is_complex = csv_is_complex;
    struct csv_info return_info = { .status = 0, .num_rows = 0, .num_cols = 0 };
    // validating file pointers (probably unnecessary but hey, why not)
	if (inputfp) 
    {
        yyin = inputfp;
    } 
    else 
    {
        fprintf(stderr, "Error: Input file does not exist.\n"); // make this error message better
        return_info.status = 2;
        return return_info;
    }
    if (outputfp)
    {
        yyout = outputfp;
    }
    else
    {
        fprintf(stderr, "Error: Pointer to output file was null.\n");
        return_info.status = 3;
        return return_info;
    }

    // running the lexer
	yylex();

    // checking the size of the last row
    if (num_rows <= 1) 
    {
        num_cols = entries_in_current_row;
    } 
    else if (entries_in_current_row != num_cols) 
    {
        fprintf(stderr, "Error: Uneven rows: Row %d is %d entries long, while other rows are %d entries long.\n", num_rows, entries_in_current_row, num_cols);
        ++error_counter;
    }

    // ensuring the user hasn't tried to make a complex matrix
    if (num_rows > 1 && is_complex) 
    {
        fprintf(stderr, "Error: Cannot store complex values to a matrix.\n");
        ++error_counter;
    }

    // checking to see if any errors/warnings occurred, displaying a message and exiting if needed.
    if (error_counter)
    {
        fprintf(stderr, "%d Errors generated.\nConversion of CSV to .8x* failed.\n", error_counter);
        return_info.status = 4;
        return return_info;
    }

    // debug info
	printf("\nrows: %d\n", num_rows);
	printf("cols: %d\n", num_cols);

    return_info.num_rows = num_rows;
    return_info.num_cols = num_cols;
    return_info.status = 0;
    return return_info;
}