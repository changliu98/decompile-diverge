size_t sdsll2str(char *s, long long value) {
    char *p;
    unsigned long long v;
    size_t len;
    char temp;

    // Handle negative numbers by taking the absolute value
    if (value < 0) {
        v = (unsigned long long)(-value);
    } else {
        v = (unsigned long long)value;
    }

    p = s;

    // Generate digits in reverse order
    do {
        *p = (v % 10) + '0';
        p++;
        v /= 10;
    } while (v != 0);

    // Add the negative sign if the original number was negative
    if (value < 0) {
        *p = '-';
        p++;
    }

    // Calculate the length of the resulting string
    len = p - s;

    // Null-terminate the string
    *p = '\0';

    // Reverse the string in-place
    p--;
    while (s < p) {
        temp = *s;
        *s = *p;
        *p = temp;
        s++;
        p--;
    }

    return len;
}