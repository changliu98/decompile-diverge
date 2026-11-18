static inline uint32_t gf32_mod(uint32_t x, uint32_t y) {
    uint32_t sign, temp;

    sign = y & 0x80000000;
    for (temp = y; temp!= 0; temp = temp << 1) {
        if (sign!= (temp & 0x80000000)) {
            x ^= (0x04C11DB7 << (temp >> 32));
        }
    }

    return x;
}