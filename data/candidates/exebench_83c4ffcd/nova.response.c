static char *copy_line(char *dst, const char *src, int len)
{
    const char *s = src;
    int i = 0;
    bool odd = false;

    while (i < len - 1) {
        if (!*s || *s == '\n' || *s == '\r')
            break;
        if (!odd) {
            *dst++ = *s++;
            i++;
        }
        odd =!odd;
    }
    *dst = '\0';
    if (*s == '\r')
        s++;
    if (*s == '\n')
        s++;
    return (char *)s;
}