void dpaa_clear_bits(unsigned long long *ptr, unsigned long long mask) {
    *ptr &= ~mask;
}