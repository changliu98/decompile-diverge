void bitmap_set(unsigned long *bitmap, int start, int count) {
    unsigned long *ptr = bitmap + (start / 64);
    int end = start + count;
    int bits_to_end = 64 - (start % 64);
    unsigned long mask = ~0UL << (start % 64);

    while (count - bits_to_end >= 0) {
        *ptr |= mask;
        count -= bits_to_end;
        bits_to_end = 64;
        mask = ~0UL;
        ptr++;
    }

    if (count != 0) {
        unsigned long end_mask;
        if ((end % 64) != 0) {
            end_mask = (1UL << (end % 64)) - 1;
        } else {
            end_mask = ~0UL;
        }
        mask &= end_mask;
        *ptr |= mask;
    }
}