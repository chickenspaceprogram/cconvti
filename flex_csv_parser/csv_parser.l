CSV_ENTRY   -?[0-9]+"."?[0-9]*([eE][+-][0-9]+)?

%{
    int num_rows = 0;
    int num_cols = 0;
    int entries_in_current_row = 0;
%}

%%

,{CSV_ENTRY}   {
        ECHO;
        ++entries_in_current_row;
}

^{CSV_ENTRY}    {
        if (num_rows <= 1) 
        {
            num_cols = entries_in_current_row;
        } 
        else if (entries_in_current_row != num_cols) {
            fprintf(stderr, "Uneven rows: Row %d is %d entries long, while other rows are %d entries long.\ncconvti exiting...\n", num_rows, entries_in_current_row, num_cols);
            exit(1); // make this suck less
        }
        ECHO;
        ++num_rows;
        entries_in_current_row = 1;
    }
\n  {
    yytext[0] = ',';
    ECHO;
}

.   {
        fprintf(stderr, "Invalid entry `%s`.\n", yytext);
        exit(1);
    }
%%

/*
could totally just be a wrapper function for yylex doing a bit of error handling, etc.
*/
int main(void)
{
	char *filename = "mycsv.csv";
	FILE *fp = fopen(filename, "r");
	if(fp) {
        yyin = fp;
    } else {
        fprintf(stderr, "Could not find the file at `%s`.\ncconvti exiting...\n", filename);
    }
	yylex();
    if (num_rows <= 1) 
    {
        num_cols = entries_in_current_row;
    } 
    else if (entries_in_current_row != num_cols) {
        fprintf(stderr, "Uneven rows: Row %d is %d entries long, while other rows are %d entries long.\ncconvti exiting...\n", num_rows, entries_in_current_row, num_cols);
        exit(1); // make this suck less
    }
	printf("\nrows: %d\n", num_rows);
	printf("cols: %d\n", num_cols);
	return 0;
}