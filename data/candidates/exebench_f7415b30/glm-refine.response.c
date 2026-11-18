int __cdecl dummywc_mbtowc(int *pwc, const char *s, size_t n)
{
    // Check if the buffer size is zero or if the string starts with a null terminator
    if (n == 0 || s[0] == '\0')
        return 0;

    // Cast the single-byte character to the wide character type and store it
    *pwc = (unsigned char)s[0];
    
    // Return the number of bytes consumed (always 1 for this dummy implementation)
    return 1;
}