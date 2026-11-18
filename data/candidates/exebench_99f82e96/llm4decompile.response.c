char *itoa(int value, char *str, int base)
{
    static const char *digits = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
    char *pdig = str;
    const char *pdigits = digits + 35;

    if (base < 2 || base > 36)
    {
        *pdig = '\0';
        return str;
    }

    if (value < 0)
    {
        *pdig++ = '-';
    }

    do
    {
        *pdig++ = pdigits[value % base];
        value /= base;
    }
    while (value != 0);

    *pdig = '\0';

    for (char *begin = str, *end = pdig; begin < end--; ++begin)
    {
        const char temp = *begin;
        *begin = *end;
        *end = temp;
    }

    return str;
}