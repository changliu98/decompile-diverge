static void func0(short *dest, const unsigned char *src, size_t len)
{
    size_t i;

    for (i = 0; i < len; i++) {
        uint16_t s = src[i];
        uint16_t u = (s << 8) - 0x8000;
        dest[i] = (int16_t)u;
    }
}