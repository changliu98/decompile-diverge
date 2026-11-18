int __cdecl func0(const char *str, char ch)
{
    int last_index = -1;
    int length = strlen(str);

    // Iterate through the string to find the last occurrence of 'ch'
    for (int i = 0; i < length; ++i)
    {
        if (str[i] == ch)
            last_index = i;
    }

    // If the character was not found, return -1. Otherwise, return the 1-based index.
    return (last_index == -1) ? -1 : last_index + 1;
}