static int utf8proc_next(unsigned char *s, long len, int *c)
{
    unsigned char *e;
    unsigned int u;
    int uca;
    *c = -1;
    if (len == 0)
        return 0;
    if (len < 0)
        len = 4;
    else
        len = (unsigned long)len;
    e = s + len;
    u = s[0];
    if (u < 0x80) {
        *c = u;
        return 1;
    }
    if (u - 0xc2 > 0x32)
        return -3;
    if (u < 0xe0) {
        if (s + 1 >= e)
            return -3;
        if ((*s & 0xc0) != 0xc0)
            return -3;
        if ((*s & 0xff) < 0xe0 || (*s & 0xff) > 0xef)
            return -3;
        if (s[1] & 0xc0)
            return -3;
        *c = (s[0] & 0x1f) << 6 | (s[1] & 0x3f);
        return 2;
    }
    if (u - 0xe0 > 0x10)
        return -3;
    if (u < 0xf0) {
        if (s + 2 >= e)
            return -3;
        if (((s[0]) & 0xc0) != 0xc0 || ((s[1]) & 0xc0) != 0xc0)
            return -3;
        if (s[2] & 0xc0)
            return -3;
        if (u == 0xed && s[1] > 0x9f)
            return -3;
        uca = (s[0] & 0xf) << 12 | (s[1] & 0x3f) << 6 | (s[2] & 0x3f);
        if (uca < 0x1000)
            return -3;
        *c = uca;
        return 3;
    }
    if (s + 3 >= e)
        return -3;
    if (((s[0]) & 0xc0) != 0xc0 || ((s[1]) & 0xc0) != 0xc0 || ((s[2]) & 0xc0) != 0xc0)
        return -3;
    if (u == 0xf0 && s[1] < 0x90)
        return -3;
    if (u == 0xf4 && s[1] > 0x8f)
        return -3;
    *c = (s[0] & 0x07) << 18 | (s[1] & 0x3f) << 12 | (s[2] & 0x3f) << 6 | (s[3] & 0x3f);
    return 4;
}