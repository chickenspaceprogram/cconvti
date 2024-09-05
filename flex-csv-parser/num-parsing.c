#include "num-parsing.h"

/**
 * Increments the mantissa of `number` by 1, without regard for its sign or exponent.
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

/**
 * Writes `number` to the file at `fp`.
 */
void write_real_number(struct real_number number, FILE *fp) {
    fputc(number.flags, fp);
    fputc(number.exponent, fp);
    for (int i = 0; i < 7; ++i) {
        fputc(number.mantissa[i], fp);
    }
}

/**
 * Parses the text string at `number` into a `real_number` struct.
 * If the number at `number` is the real or imaginary part of a complex number, set `is_complex` to a nonzero value.
 * Otherwise, set `is_complex` to zero.
 */
struct real_number parse_real_number(char *number, int is_complex) {
    int i = 0;
    int is_in_mantissa = 1;
    int found_decimal_point = 0;
    int on_leading_zero = 1;
    int num_digits = 0;
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
                        return_number.exponent += num_digits - 1; // something like 123e... should get +2 to its exponent. 000123e will also get +2 overall, since it gets +5 from this and -3 from the zeroes.
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
                    if (num_digits == 14 && number[i] >= 5) 
                    {
                        return_number = inc_mantissa(return_number); // since rounding a negative down and a positive up both increment the mantissa without regard to the sign, inc_mantissa works here
                        break;
                    } 
                    else if (num_digits >= 14) 
                    {
                        break;
                    }

                    if (num_digits % 2 == 0)
                    {
                        number[i] <<= 4; // bitshifting number left by 4 since this digit is the most significant nibble in this byte
                    }
                
                    return_number.mantissa[num_digits / 2] += number[i];
                    ++num_digits;
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
            }
            return_number.exponent += (char) exponent_from_csv;
            return return_number;
        }
        ++i;
    }
    if (!found_decimal_point) 
    {
        return_number.exponent += num_digits - 1;
    }
    return return_number;
}