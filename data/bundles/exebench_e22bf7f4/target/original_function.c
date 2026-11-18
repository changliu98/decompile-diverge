void reverse(char s[])
{
    char c;
    int i, len;
    i = 0;
    len = 0;
    while (s[i++] != '\0')
    {
        len++;
    }
    for (i = 0; i < len / 2; i++)
    {
        c = s[i];
 s[i] = s[len - 1 - i];
 s[len - 1 - i] = c;
    }
}