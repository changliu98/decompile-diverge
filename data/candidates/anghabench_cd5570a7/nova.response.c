unsigned long long it_advance(unsigned long long x) {
    if (x & 0x00000000FFFFFFFFULL) {
        x = (x & 0x00000000FFFFFFFFULL) |
            (((x & 0xFFFFFFFF00000000ULL) >> 1) |
             ((x & 0x0000000000000001ULL) << 63));
    } else {
        x = (x >> 1) | (x << 63);
    }
    return x;
}