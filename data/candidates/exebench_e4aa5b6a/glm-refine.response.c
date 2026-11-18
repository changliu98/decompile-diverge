int __cdecl util_read_dec(const char *str, int *result)
{
    long long val = 0;
    int i = 0;
    int neg = 0;
    const char *p = str;

    *result = 0;

    // Check for negative sign
    if (*str == '-')
    {
        neg = 1;
        p = str + 1;
        i = 1;
    }

    // Parse digits
    while (*p)
    {
        int digit = *p - '0';
        if ((unsigned int)digit >= 10)
            break;

        val = 10 * val + digit;

        // The original code relies on 32-bit truncation when assigning back to `*result`.
        // We explicitly check the 32-bit range to preserve the exact semantics.
        if (val > 0x7FFFFFFF)
            break;

        p++;
        i++;
    }

    *result = (int)val;

    if (!neg)
        return i;

    // If a negative sign was present but no digits followed, it's invalid.
    if (i != 1)
    {
        *result = -*result;
        return i;
    }

    return 0;
}