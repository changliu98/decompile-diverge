const char *__cdecl convert_set_base(const char *s, int *base)
{
    // Default to base 10
    *base = 10;

    // If the string is NULL, return NULL
    if (!s)
        return s;

    // Check for '0' prefix indicating octal or hex
    if (s[0] == '0')
    {
        // Check if the next character is 'x' or 'X' (Hexadecimal)
        if (s[1] == 'x' || s[1] == 'X')
        {
            *base = 16;
            return s + 2; // Skip "0x" or "0X"
        }
        // If it was just '0', it falls through to return s + 1 (Octal/Zero handling)
        return s + 1;
    }

    // No prefix found, return original string pointer
    return s;
}