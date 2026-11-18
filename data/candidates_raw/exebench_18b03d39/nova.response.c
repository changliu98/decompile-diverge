static void func0(uint16_t *p) {
    uint16_t n = *p;
    uint8_t b1 = n & 0xff;
    uint8_t b2 = (n >> 8) & 0xff;
    *p = ((uint16_t)b2 << 8) | b1;
}