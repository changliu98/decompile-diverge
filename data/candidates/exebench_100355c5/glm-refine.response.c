const char *__cdecl string_to_slong(const char *str, long *number)
{
    const char *ptr = str;
    int sign = 0;
    char c = *ptr;

    // Check for sign
    if (c == '-')
    {
        sign = 1;
        ptr++;
        c = *ptr;
    }
    else if (c == '+')
    {
        ptr++;
        c = *ptr;
    }

    *number = 0;

    // Parse digits
    while (isdigit(c))
    {
        *number = (*number * 10) + (c - '0');
        ptr++;
        c = *ptr;
    }

    // Apply sign
    if (sign)
    {
        *number = -*number;
    }

    return ptr;
}