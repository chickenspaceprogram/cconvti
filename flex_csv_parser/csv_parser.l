CSV_ENTRY   -?[0-9]+"."?[0-9]*([eE][+-][0-9]+)?

%{
    #include "csv_parser.h"

    // eww globals
    int num_rows = 0;
    int num_cols = 0;
    int entries_in_current_row = 0;
    int is_complex;
    int error_counter = 0;
    int warning_counter = 0;
/*
A real number, represented as it is on TI-8x calculators.
*/
struct real_number {
unsigned char flags;
unsigned char exponent;
unsigned char mantissa[7];
};

/*
Writes number to the file at filename.
*/
void write_real_number(struct real_number number, FILE *fp) {
    fputc(number.flags, fp);
    fputc(number.exponent, fp);
    for (int i = 0; i < 7; ++i) {
        fputc(number.mantissa[i], fp);
    }
}

/*
Increments the mantissa of `number` by 1, without regard for its sign or exponent.
*/
struct real_number inc_mantissa(struct real_number number) {
    int current_digit;
    // the happy case
    for (int i = 13; i >= 0; --i) {
        if (i % 2 == 0) {
            number.mantissa[i / 2] += 0x10;
            current_digit = (number.mantissa[i / 2] & 0xF0) >> 4;
        } else {
            ++number.mantissa[i / 2];
            current_digit = number.mantissa[i / 2] & 0x0F;
        }
        if (current_digit < 10) {
            return number;
        }
    }
    // since we are only incrementing by one, if we've gotten this far, every digit had to be a 9
    number.mantissa[0] = 0x10;
    for (int i = 1; i < 7; ++i) {
        number.mantissa[i] = 0;
    }
    --number.exponent;
    return number;
}

struct real_number parse_real_number(char *number) {
    int i = 0;
    int is_in_mantissa = 1;
    int found_decimal_point = 0;
    int on_leading_zero = 1;
    int current_number_place = 0;
    int exponent_from_csv;
    struct real_number return_number = {0, 0x80, {0, 0, 0, 0, 0, 0, 0}};
    

    if (is_complex) {
        return_number.flags += 0x0C;
    }

    while (number[i] != 0) {

        if (is_in_mantissa) 
        {
            switch (number[i]) {
                case '-':
                   return_number.flags += 0x80; // flipping the first bit of the flag makes the number negative
                   break;
                case '.':
                    return_number.exponent += i - 1; // something like 3.1415 will have no change to its exponent, but 314.15 will need its exponent incremented by 2
                    found_decimal_point = 1;
                    break;
                case 'e': case 'E':
                    is_in_mantissa = 0;
                    if (!found_decimal_point) 
                    {
                        return_number.exponent += i - 1; // something like 123e... should get +2 to its exponent. 000123e will also get +2 overall, since it gets +5 from this and -3 from the zeroes.
                    }
                    break;
                case '0':
                    if (on_leading_zero) 
                    {
                        return_number.exponent -= 1;
                        break;
                    }
                default:
                    /* this case basically converts ASCII digits to BCD digits and encodes them, two to a byte.
                    good god are graphing calculators cursed lmao

                    TI deciding to store numbers this way is either insanely brilliant or completely stupid and I can't tell which */

                    on_leading_zero = 0;
                    number[i] -= '0'; // converting character from ASCII -> a number

                    // taking care of rounding
                    if (current_number_place == 14 && number[i] >= 5) 
                    {
                        return_number = inc_mantissa(return_number); // since rounding a negative down and a positive up both increment the mantissa without regard to the sign, inc_mantissa works here
                        break;
                    } 
                    else if (current_number_place >= 14) 
                    {
                        break;
                    }

                    if (current_number_place % 2 == 0)
                    {
                        number[i] <<= 4; // bitshifting number left by 4 since this digit is the most significant nibble in this byte
                    }
                
                    return_number.mantissa[current_number_place / 2] += number[i];
                    ++current_number_place;
            }
        }
        else 
        {
            // code for what to do when we are at exponent
            
            sscanf(number + i + 1, "%d", &exponent_from_csv);
            if (number[i] == '-')
            {
                exponent_from_csv = -exponent_from_csv;
            }
            if (exponent_from_csv > 99 || exponent_from_csv < -99)
            {
                fprintf(stderr, "Warning: Exponent %d is out of bounds and may cause overflow errors.", exponent_from_csv);
                ++warning_counter;
            }
            return_number.exponent += (char) exponent_from_csv;
            return return_number;
        }
        ++i;
    }
    if (!found_decimal_point) 
    {
        return_number.exponent += i - 1;
    }
    return return_number;
}
%}

%%

,{CSV_ENTRY}   {
        write_real_number(parse_real_number(yytext + 1), yyout);
        ++entries_in_current_row;
}

^{CSV_ENTRY}    {
        if (num_rows <= 1) 
        {
            num_cols = entries_in_current_row;
        } 
        else if (entries_in_current_row != num_cols) {
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
Contains some necessary information about the file.
*/
struct file_info 
{
    int num_rows;
    int num_cols;
};


/*
Reads and parses CSV into the format used by TI-BASIC.
Returns status. If the returned value is nonzero, an error occurred.
*/
int read_csv(FILE *input_fileptr, FILE *output_fileptr, int csv_is_complex)
{
    is_complex = csv_is_complex;

    // validating file pointers (probably unnecessary but hey, why not)
	if (input_fileptr) 
    {
        yyin = input_file_ptr;
    } 
    else 
    {
        fprintf(stderr, "Error: Could not find input file.\n"); // make this error message better
        return 1;
    }
    if (output_fileptr)
    {
        yyout = output_fileptr;
    }
    else
    {
        fprintf(stderr, "Error: Pointer to output file was null.\n");
        return 1;
    }

    // running the lexer
	yylex();

    // checking the size of the last row
    if (num_rows <= 1) 
    {
        num_cols = entries_in_current_row;
    } 
    else if (entries_in_current_row != num_cols) {
        fprintf(stderr, "Error: Uneven rows: Row %d is %d entries long, while other rows are %d entries long.\n", num_rows, entries_in_current_row, num_cols);
        ++error_counter;
    }

    // ensuring the user hasn't tried to make a complex matrix
    if (num_rows > 1 && is_complex) {
        fprintf(stderr, "Error: Cannot store complex values to a matrix.\n")
        ++error_counter;
    }

    // checking to see if any errors/warnings occurred, displaying a message and exiting if needed.
    if (error_counter || warning_counter)
    {
        if (error_counter)
        {
            fprintf(stderr, "%d Errors, ", error_counter);
        }
        if (warning_counter)
        {
            fprintf(stderr, "%d Warnings ", warning_counter);
        }
        fprintf(stderr, "occurred.\n");
        if (error_counter)
        {
            fprintf("Conversion of CSV to .8x* format failed.\n");
            return 1;
        }
    }

    // debug info
	printf("\nrows: %d\n", num_rows);
	printf("cols: %d\n", num_cols);
    return 0;
}