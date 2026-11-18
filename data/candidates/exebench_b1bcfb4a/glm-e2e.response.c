void dpaa_set_bits(unsigned long long mask, unsigned long long *addr) {
    *addr |= mask;
}