void BMP_getGenBmp16Palette(uint8_t *src, uint16_t *dst) {
    uint16_t *p_src = (uint16_t *)(src + 4);
    uint16_t *p_dst = dst;
    uint16_t count = 16;

    while (count != 0) {
        count--;
        *p_dst++ = *p_src++;
    }
}