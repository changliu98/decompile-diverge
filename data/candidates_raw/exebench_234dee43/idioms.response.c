char *mbtowc(char *dst, char *src, int len)
{
    int c;
    int n;
    int bits;
    int i;
    unsigned int ret;
    if ( (c = *src & 0xff) < 0x80 )
    {
        if ( dst )
            *dst = c;
        return (src + 1);
    }
    if ( (c & 0xe0) == 0xc0 )
    {
        n = 2;
        c &= ~0xe0;
    }
    else if ( (c & 0xf0) == 0xe0 )
    {
        n = 3;
        c &= ~0xf0;
    }
    else if ( (c & 0xf8) == 0xf0 )
    {
        n = 4;
        c &= ~0xf8;
    }
    else if ( (c & 0xfc) == 0xf8 )
    {
        n = 5;
        c &= ~0xfc;
    }
    else if ( (c & 0xfe) == 0xfc )
    {
        n = 6;
        c &= ~0xfe;
    }
    else
        return ((void *)0);
    bits = (n - 1) * 6;
    ret = c << bits;
    for (i = 1; i < n; i++)
    {
        bits -= 6;
        if ( (*++src & 0xc0) != 0x80 )
            return ((void *)0);
        ret |= (*src & 0x3f) << bits;
    }
    if ( dst )
        *dst = (char)ret;
    return (src + 1);
}