char *__cdecl itoa(int value, char *str, int base)
{
    char *low = str;

    if (base >= 2 && base <= 36)
    {
        char *ptr = str;
        
        // Convert the value to a string (in reverse order)
        do
        {
            *ptr++ = aZyxwvutsrqponm[value % base + 35];
            value /= base;
        }
        while (value);
        
        // Null-terminate the string
        *ptr = '\0';
        
        // Reverse the string in-place
        char *high = ptr - 1;
        while (low < high)
        {
            char tmp = *low;
            *low++ = *high;
            *high-- = tmp;
        }
    }
    else
    {
        // If the base is invalid, return an empty string
        *str = '\0';
    }
    
    return str;
}