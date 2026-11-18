int StrSafeCopy(char *dst, const char *src, int size)
{
    char *p = dst;
    char *q = src;
    int len = size;
    while (--len && (*p++ = *q++)) ;
    if (!len) {
        if (size) *p = '\0';
        while (*q++);
    }
    return q - src - 1;
}