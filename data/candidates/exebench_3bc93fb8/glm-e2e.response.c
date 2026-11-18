void bitmap_set(uint64_t *bitmap, int start, int len) {
    uint64_t *p = bitmap + (start / 64);
    int end = start + len;
    int bits_to_set = 64 - (start % 64);
    uint64_t mask = ~0ULL << (start % 64);

    while (len - bits_to_set >= 0) {
        *p |= mask;
        len -= bits_to_set;
        bits_to_set = 64;
        mask = ~0ULL;
        p++;
    }

    if (len != 0) {
        uint64_t end_mask;
        if ((end % 64) != 0) {
            end_mask = (1ULL << (end % 64)) - 1;
        } else {
            end_mask = ~0ULL;
        }
        mask &= end_mask;
        *p |= mask;
    }
}