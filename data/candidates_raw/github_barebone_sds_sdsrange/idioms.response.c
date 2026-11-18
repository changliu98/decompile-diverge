void sdsrange(char *s, long start, long end)
{
    unsigned long len = sdslen(s);
    unsigned long newlen;
    if (len == 0)
        return;
    if (start < 0) {
        start += len;
        if (start < 0)
            start = 0;
    }
    if (end < 0) {
        end += len;
        if (end < 0)
            end = 0;
    }
    if (start > end)
        newlen = 0;
    else
        newlen = end - start + 1;
    if (newlen == 0)
        return;
    if (start >= len)
        newlen = 0;
    else if (end >= len)
        newlen = len - start;
    if (start > 0 && newlen > 0)
        memmove(s, s + start, newlen);
    s[newlen] = '\0';
    sdssetlen(s, newlen);
}