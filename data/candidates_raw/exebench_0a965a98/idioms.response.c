int strncpy(char *dest, char *src, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (src[i] == '\0')
            break;
    }
    dest[i] = '\0';
    return 0;
}