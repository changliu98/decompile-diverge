int set_bit(int *flags, int bit) {
    *flags = *flags | (1 << bit);
    return *flags;
}