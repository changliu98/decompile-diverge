static void swapdouble(void *v)
{
    uint32_t *p = v;
    uint32_t t;

    t = (p[0] & 0x000000ff) << 24 |
        (p[0] & 0x0000ff00) << 8  |
        (p[0] & 0x00ff0000) >> 8  |
        (p[0] & 0xff000000) >> 24;
    p[0] = (p[1] & 0x000000ff) << 24 |
           (p[1] & 0x0000ff00) << 8  |
           (p[1] & 0x00ff0000) >> 8  |
           (p[1] & 0xff000000) >> 24;
    p[1] = t;
}