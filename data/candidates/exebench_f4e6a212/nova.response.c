static void mix_16h_to_32_s2(uint32_t *x, uint16_t *y, int len)
{
    len >>= 1;
    do {
        *x += *y >> 1;
        *x += *++y >> 1;
        *x += *y >> 1;
        *x += *++y >> 1;
    } while (--len);
}