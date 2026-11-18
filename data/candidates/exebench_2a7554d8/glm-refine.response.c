int replace(char *str, char find, char replace_with)
{
    char *ptr = str;

    // Find the first occurrence of the character
    while ((ptr = strchr(ptr, find)) != NULL)
    {
        // Replace it
        *ptr = replace_with;
        
        // Move to the next character to continue searching
        ptr++;
    }

    return 0;
}