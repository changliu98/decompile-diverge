void __cdecl string_reverse(char *p)
{
    char *q = p;
    char *end;

    // Find the null terminator
    while (*q)
    {
        ++q;
    }
    
    // Set end pointer to the last character before the null terminator
    end = q - 1;

    // Reverse the string in-place using XOR swap
    while (p < end)
    {
        *p ^= *end;
        *end ^= *p;
        *p++ ^= *end;
        --end;
    }
}