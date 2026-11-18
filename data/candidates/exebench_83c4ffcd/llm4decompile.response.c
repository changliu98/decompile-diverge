char *copy_line(char *where, char *what, int n)
{
    int i;

    for (i = 0; i < n-1 && *what && *what!='\n' && *what!='\r'; i++)
        *where++ = *what++;
    *where = 0;
    if (*what=='\r') what++;
    if (*what=='\n') what++;
    return what;
}