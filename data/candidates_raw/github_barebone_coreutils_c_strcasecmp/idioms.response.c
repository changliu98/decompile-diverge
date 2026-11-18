int strcasecmp(char *s1, char *s2)
{
    unsigned char *p1 = (const unsigned char *) s1;
    unsigned char *p2 = (const unsigned char *) s2;
    unsigned char c1; unsigned char c2;
    if (s1 == s2)
        return 0;
    do
    {
        c1 = c_tolower(*p1);
        c2 = c_tolower(*p2);
        if (c1 == '\0' || c1 != c2)
            break;
        p1++;
        p2++;
    }
    while (1);
    return c1 - c2;
}