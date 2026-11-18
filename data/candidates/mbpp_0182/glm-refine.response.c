void __cdecl func0(
        char *string,
        char *uppercase_characters,
        char *lowercase_characters,
        char *numerical_characters,
        char *special_characters)
{
    size_t i;
    size_t len;
    int upper_idx = 0;
    int lower_idx = 0;
    int num_idx = 0;
    int special_idx = 0;

    len = strlen(string);
    for (i = 0; i < len; ++i)
    {
        char c = string[i];
        
        // Check character type using standard ctype.h masks
        // 0x100 -> _ISupper, 0x200 -> _ISlower, 0x800 -> _ISdigit
        if (isupper((unsigned char)c))
        {
            uppercase_characters[upper_idx++] = c;
        }
        else if (islower((unsigned char)c))
        {
            lowercase_characters[lower_idx++] = c;
        }
        else if (isdigit((unsigned char)c))
        {
            numerical_characters[num_idx++] = c;
        }
        else if (c == ',' || c == '.' || c == '!' || c == '?')
        {
            special_characters[special_idx++] = c;
        }
    }

    // Null-terminate all destination buffers
    uppercase_characters[upper_idx] = '\0';
    lowercase_characters[lower_idx] = '\0';
    numerical_characters[num_idx] = '\0';
    special_characters[special_idx] = '\0';
}