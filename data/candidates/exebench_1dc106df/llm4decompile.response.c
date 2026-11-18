char *i2hs(uint32_t n, char *ds)
{
    char *ds_start = ds;
    char ts[32];
    char *tsp = ts;
    const char *h = "0123456789ABCDEF";

    *tsp = '\0';
    while (n != 0) {
        *++tsp = h[n & 0xf];
        n >>= 4;
    }
    if (*tsp == '\0') {
        *++tsp = '0';
    }
    while (*tsp != '\0') {
        *ds++ = *tsp--;
    }
    return ds_start;
}