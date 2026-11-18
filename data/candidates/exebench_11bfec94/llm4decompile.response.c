void to_hex(uint32_t v, char *c)
{
    const char *s_0123456789ABCDEF = "0123456789ABCDEF";
    int i;
    for (i = 3; i >= 0; i--)
    {
        c[i] = s_0123456789ABCDEF[v % 16];
        v /= 16;
    }
    c[4] = '\0';
}