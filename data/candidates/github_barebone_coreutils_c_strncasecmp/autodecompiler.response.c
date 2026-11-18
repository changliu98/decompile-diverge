int
c_strncasecmp(const char *s1, const char *s2, size_t n)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    unsigned char c1, c2;
    int result;

    if (p1 == p2 || n == 0)
        return 0;

    while (n-- > 0) {
        c1 = c_tolower(*p1);
        c2 = c_tolower(*p2);

        if (n == 0 || c1 == '\0' || c1 != c2)
            return c1 - c2;

        p1++;
        p2++;
    }

    return c1 - c2;
}