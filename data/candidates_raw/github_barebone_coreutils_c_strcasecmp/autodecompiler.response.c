int
c_strcasecmp(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    unsigned char c1, c2;
    int result;

    if (p1 == p2)
        return 0;

    while (1) {
        c1 = c_tolower(*p1);
        c2 = c_tolower(*p2);

        if (c1 == '\0' || c1 != c2)
            break;

        p1++;
        p2++;
    }

    result = c1 - c2;
    return result;
}