int func0(char *str, char *substr)
{
    int c = 0;
    int len = strlen(str);
    int sublen = strlen(substr);
    int i;

    if (len == 0)
    {
        return 0;
    }

    for (i = 0; i <= len - sublen; i++)
    {
        if (strncmp(&str[i], substr, sublen) == 0)
        {
            c++;
        }
    }

    return c;
}