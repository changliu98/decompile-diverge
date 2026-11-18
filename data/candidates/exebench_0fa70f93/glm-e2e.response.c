void atomic_clear_mask(unsigned long long mask, unsigned long long *addr) {
    *addr &= ~mask;
}