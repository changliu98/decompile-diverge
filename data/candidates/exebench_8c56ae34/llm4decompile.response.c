void Reverse(char s[])
{
    int c, i, j;

    for (i = 0; s[i] != '\0'; ++i)
        ;

    if (s[--i] == '\n')
        --i;

    for (j = 0; j < i; ++j, --i)
    {
        c = s[j];
        s[j] = s[i];
        s[i] = c;
    }
}