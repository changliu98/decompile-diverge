uint64_t gf32_mod(uint64_t a, int b) {
    int i = b;
    while (i >= 32) {
        if (a & (1ULL << i)) {
            a ^= (0x1edc6f41ULL << (i - 32));
        }
        i--;
    }
    return a;
}