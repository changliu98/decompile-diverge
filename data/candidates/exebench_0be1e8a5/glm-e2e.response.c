void short_to_string(char *str, short num) {
    short remainder = 0;
    char digit;

    // Extract ten-thousands digit (10000)
    digit = (num - remainder) / 10000;
    remainder += digit * 10000;
    *str++ = digit + '0';

    // Extract thousands digit (1000)
    digit = (num - remainder) / 1000;
    remainder += digit * 1000;
    *str++ = digit + '0';

    // Extract hundreds digit (100)
    digit = (num - remainder) / 100;
    remainder += digit * 100;
    *str++ = digit + '0';

    // Extract tens digit (10)
    digit = (num - remainder) / 10;
    remainder += digit * 10;
    *str++ = digit + '0';

    // Extract ones digit (1)
    digit = num - remainder;
    remainder += digit;
    *str++ = digit + '0';

    // Null-terminate the string
    *str = '\0';
}