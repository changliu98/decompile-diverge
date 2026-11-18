void endian_swap16bit(uint16_t *ptr) {
    uint16_t val = *ptr;
    // Swap the high and low bytes
    *ptr = (val >> 8) | (val << 8);
}