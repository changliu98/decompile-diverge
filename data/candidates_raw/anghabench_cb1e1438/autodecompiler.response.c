unsigned long long crc32(unsigned long long crc, int bit) {
    int i = bit;
    for (i = bit; i >= 32; i--) {
        if (crc & (1ULL << i)) {
            crc ^= 0x1EDC6F41ULL << (i - 32);
        }
    }
    return crc;
}