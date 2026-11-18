static void func0(uint32_t *x, uint16_t *y, int len)
{
    len >>= 1;
    do {
        *x += *y >> 1;
        *x += *++y >> 1;
        *x += *y >> 1;
        *x += *++y >> 1;
    } while (--len);
}