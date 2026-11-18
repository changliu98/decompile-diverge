char *sdscpylen(char *dst, char *src, unsigned long n)
{
    char *d = dst;
    if (sdsalloc(dst) < n) {
        d = sdsMakeRoomFor(dst, n - sdslen(dst));
        if (d == ((void *)0))
            return ((void *)0);
    }
    memcpy(d, src, n);
    d[n] = '\0';
    sdssetlen(d, n);
    return d;
}