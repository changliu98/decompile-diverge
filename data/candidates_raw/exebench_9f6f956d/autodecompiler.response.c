int mystrncpy(char *dest, char *source, int num)
{
    int i;
    int length;

    if ((num < 2) || (source == NULL) || (dest == NULL))
    {
        if (dest != NULL)
            dest[0] = '\0';
        length = 0;
    }
    else
    {
        for (i = 0; ; i++)
        {
            if ((source[i] == '\0') || (i > (num - 2)))
            {
                dest[i] = '\0';
                length = i;
                break;
            }
            dest[i] = source[i];
        }
    }
    return(length);
}