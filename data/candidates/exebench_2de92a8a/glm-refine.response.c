int __cdecl sprint_int_number_nonlocalized(char *str, int value, int min_digits, int show_plus_sign)
{
    int digit;
    int length = 0;
    int base = 1000000000;
    int is_leading_zero = 1;
    int abs_value = value;

    // Clamp negative minimum digits to 0
    if (min_digits < 0)
        min_digits = 0;

    // If minimum precision is greater than 9, we will print all leading zeros
    if (min_digits > 9)
        is_leading_zero = 0;

    // Handle sign
    if (value >= 0)
    {
        if (show_plus_sign)
        {
            str[length++] = '+';
        }
    }
    else
    {
        str[length++] = '-';
        abs_value = -value;
    }

    // Extract and print each digit
    for (int i = 10; i > 0; --i)
    {
        // If we reach the threshold of minimum digits, force printing
        if (min_digits == i)
            is_leading_zero = 0;

        digit = abs_value / base;
        abs_value %= base;

        if (digit || !is_leading_zero)
        {
            str[length++] = digit + '0';
            is_leading_zero = 0;
        }

        base /= 10;
    }

    // Handle the special case where the value is 0 and no digits were printed
    if (is_leading_zero)
    {
        str[length++] = '0';
    }

    str[length] = '\0';
    return length;
}