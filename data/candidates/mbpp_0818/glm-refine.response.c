int __cdecl func0(const char *str)
{
    int lower_ctr = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i)
    {
        // Check if the character is a lowercase ASCII letter ('a' to 'z')
        if (str[i] >= 'a' && str[i] <= 'z')
            ++lower_ctr;
    }
    
    return lower_ctr;
}