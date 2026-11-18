void remove_all_chars(char *str, char c)
{
    char *p, *q;
    for(p = str, q = str; ; p++, q++)
    {
        while(*p != '\0')
        {
            *q = *p++;
            q += (*q != c);
        }
        break;
    }
    *q = '\0';
}