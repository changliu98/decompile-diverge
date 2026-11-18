void bn_reverse(unsigned char *s, int len)
{
    int ix, iy;
    unsigned char t;

    for (ix = 0, iy = len - 1; ix < iy; ix++, iy--) {
        t = s[ix];
        s[ix] = s[iy];
        s[iy] = t;
    }
}