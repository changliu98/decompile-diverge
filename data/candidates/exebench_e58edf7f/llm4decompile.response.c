void toUpperCase(char *str)
{
    int i = 0;
    char c;

    while (str[i] != 0)
    {
        c = 'a';
        while (c <= 'z')
        {
            if (str[i] == c)
                str[i] = str[i] - 32;
            c++;
        }
        i++;
    }
}