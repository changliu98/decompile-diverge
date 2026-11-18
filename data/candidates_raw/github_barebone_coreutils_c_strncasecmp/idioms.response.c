int istrnicmp(char *s1, char *s2, unsigned long n)
{
    unsigned char *p1 = (const unsigned char *) s1;
    unsigned char *p2 = (const unsigned char *) s2;
    unsigned char c1; unsigned char c2;
    if (s1 == s2 || n == 0)
        return 0;
    do {
        c1 = c_tolower(*p1);
        c2 = c_tolower(*p2);
    } while (--n != 0 && c1 != 0 && c1 == c2);
    return c1 - c2;
}