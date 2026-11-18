char *a0123456789abcd = "0123456789abcdef";

char *__cdecl xtoa(unsigned __int64 value, char *string, int radix, int is_neg)
{
    char buf[33];
    char *p = buf;
    char *start = string;

    // Generate the digits in reverse order
    do
    {
        *p++ = a0123456789abcd[(value % radix) & 0xF];
        value /= (unsigned __int64)radix;
    }
    while (value);

    // Append the negative sign if necessary
    if (is_neg)
    {
        *p++ = '-';
    }

    // Reverse the generated string and write it to the output buffer
    do
    {
        *string++ = *(--p);
    }
    while (p != buf);

    *string = '\0';
    return start;
}