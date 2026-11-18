void clear_bit(int bit, uint64_t *addr) {
    uint64_t mask = 1ULL << (bit % 64);
    uint64_t *p = addr + (bit / 64);
    *p &= ~mask;
}