void clear_bit(int bit, unsigned long *addr) {
    *addr &= ~(1UL << bit);
}