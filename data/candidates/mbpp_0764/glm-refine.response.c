int __cdecl count_digits(const char *str)
{
    int count = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i)
    {
        // Check if the character is a numerical digit ('0' - '9')
        if (str[i] >= '0' && str[i] <= '9')
            ++count;
    }
    
    return count;
}