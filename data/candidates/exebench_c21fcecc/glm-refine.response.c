int __cdecl StrSafeCopy(char *dst, const char *src, int size)
{
    const char *s = src;
    int n = size;

    if (size)
    {
        n = size - 1;
        if (size != 1)
        {
            // Copy up to size - 1 characters from src to dst
            do
            {
                char c = *s++;
                *dst++ = c;
                if (!c)
                    break;
                --n;
            }
            while (n);
        }
    }

    // If the destination buffer was exactly filled (n == 0), 
    // ensure null-termination and fully traverse the remaining source string.
    if (!n)
    {
        if (size)
            *dst = 0; // Null-terminate the destination buffer
        
        // Traverse the rest of the source string to find its true end
        while (*s++)
            ;
    }

    // Return the length of the source string (excluding the null terminator)
    return (int)(s - src) - 1;
}