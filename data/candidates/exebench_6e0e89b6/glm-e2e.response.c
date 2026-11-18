void clear_bit(int bit, uint64_t *bitmap) {
    bitmap[bit >> 6] &= ~(1ULL << (bit & 0x3f));
}