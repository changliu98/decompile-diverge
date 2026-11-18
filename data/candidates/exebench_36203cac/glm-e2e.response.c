void set_bit(int bit, uint64_t *bitmap) {
    bitmap[bit / 64] |= (1ULL << (bit & 63));
}