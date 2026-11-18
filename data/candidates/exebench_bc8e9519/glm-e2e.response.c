void generic_set_bit(int nr, unsigned long *addr) {
    unsigned long mask = 1UL << (nr % 32);
    unsigned long *p = addr + (nr / 32);
    *p |= mask;
}