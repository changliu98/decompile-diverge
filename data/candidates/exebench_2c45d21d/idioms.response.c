char last_char(char *str)
{
    char *s = str;
    char c;
    if (!str || !*str)
        return '\0';
    while (*s)
        s++;
    s--;
    c = *s;
    *s = '\0';
    return c;
}