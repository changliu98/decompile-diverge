char *str_chrcut(char *str, char chr)
{
    char *ptr = str;
    while (*ptr)
    {
        if (*ptr == chr)
        {
            *ptr = '\0';
        }
        ptr++;
    }
    return str;
}