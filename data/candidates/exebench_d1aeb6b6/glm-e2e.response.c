void bitmap_clear(uint64_t *map, int start, int len) {
    if (len <= 0) return;

    uint64_t *ptr = &map[start / 64];
    int end = start + len;
    int bits_to_end = 64 - (start % 64);
    uint64_t start_mask = ~0ULL << (start % 64);

    while (len - bits_to_end >= 0) {
        // Clear the bits in the current 64-bit chunk
        *ptr &= ~start_mask;

        // Update remaining length and advance to the next chunk
        len -= bits_to_end;
        bits_to_end = 64;
        start_mask = ~0ULL;
        ptr++;
    }

    if (len != 0) {
        uint64_t end_mask;
        int end_mod = end % 64;
        
        if (end_mod == 0) {
            end_mask = ~0ULL;
        } else {
            end_mask = (1ULL << end_mod) - 1;
        }

        // Combine the start and end masks, and clear the bits
        start_mask &= end_mask;
        *ptr &= ~start_mask;
    }
}