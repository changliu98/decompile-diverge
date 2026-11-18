char *__cdecl itoa(int value, char *str, int base)
{
    char *ptr;
    char *low;
    int valuea;

    // Validate base
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }

    ptr = str;
    valuea = value;

    // Handle negative integers
    if (value < 0)
    {
        *str = '-';
        ptr = str + 1;
    }

    low = ptr;

    // Convert digits (this naturally handles INT_MIN correctly due to unsigned division semantics)
    do
    {
        *ptr++ = g_char_set[valuea % base + 35];
        valuea /= base;
    }
    while (valuea);

    *ptr = '\0';

    // Reverse the generated string in-place
    ptr--;
    while (low < ptr)
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }

    return str;
}