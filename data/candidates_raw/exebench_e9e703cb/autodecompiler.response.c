char *int2str(int i, char *s, int radix)
{
    char *t, *u;
    unsigned int j;
    char buf[33];

    memset(buf, 0, sizeof(buf));
    t = &buf[0];
    u = s;
    j = i;
    if ((radix < 2) || (radix > 36))
    {
        *s = '\0';
        return(s);
    }
    j = i;
    if ((i < 0) && (radix == 10))
        j = -i;
    do
    {
        *t++ = "0123456789abcdefghijklmnopqrstuvwxyz"[j % radix];
        j /= radix;
    } while (j);
    if ((i < 0) && (radix == 10))
        *t++ = '-';
    t--;
    while (t >= &buf[0])
    {
        if (*t != '\0')
            *u++ = *t;
        t--;
    }
    *u = '\0';
    return(s);
}