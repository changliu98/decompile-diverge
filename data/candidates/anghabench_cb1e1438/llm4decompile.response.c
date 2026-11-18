uint32_t gf32_mod(uint64_t x, int high_bit) {
    for (int i = high_bit; i >= 32; i -= 32) {
        if ((x >> i) & 1) {
            x ^= (uint64_t)0x1edc6f41 << (i - 32);
        }
    }
    return (uint32_t)x;
}