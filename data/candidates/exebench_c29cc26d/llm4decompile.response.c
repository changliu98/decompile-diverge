char *strcpy_x86_64_fast(char *dst, const char *src)
{
    char *s = dst;
    const char *p = src;
    int *d = (int*)dst;
    const int *s2 = (int*)src;

    do {
        *d++ = *s2++;
    } while(*(d-1) & 0xff);

    return s;
}