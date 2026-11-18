static inline void subpixels(uint32_t v, uint8_t *dst, size_t dst_len)
{
    dst[0] = (v >> 24) & 0xff;
    dst[1] = (v >> 16) & 0xff;
    dst[2] = (v >> 8) & 0xff;
    dst[3] = (v >> 0) & 0xff;
}