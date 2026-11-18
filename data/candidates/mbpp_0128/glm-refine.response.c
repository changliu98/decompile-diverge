char **__cdecl func0(int min_len, char *str, int *count)
{
    int index = 0;
    const char *delim = " ";
    
    // Iterate over all space-separated tokens in the string
    for (const char *token = strtok(str, delim); token != NULL; token = strtok(NULL, delim))
    {
        // If the token's length is strictly greater than 'min_len', store it
        if (strlen(token) > min_len)
        {
            func0_word_len[index++] = token;
        }
    }
    
    *count = index;
    return (char **)func0_word_len;
}