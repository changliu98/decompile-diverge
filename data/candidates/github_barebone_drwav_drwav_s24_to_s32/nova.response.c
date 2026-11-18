static void drwav_s24_to_s32(uint32_t *dst, const unsigned char *src, size_t len)
{
    size_t i;

    if (dst == NULL || src == NULL)
        return;
    for (i = 0; i < len; i++) {
        uint32_t val = src[3 * i];
        uint32_t val2 = src[3 * i + 1];
        uint32_t val3 = src[3 * i + 2];
        uint32_t val4 = (val << 8) | val2;
        uint32_t val5 = (val4 << 16) | val3;
        dst[i] = val5;
    }
}