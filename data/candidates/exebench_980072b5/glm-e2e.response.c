void set_bit(int bit_index, unsigned long *bitmap) {
    unsigned long mask = 1UL << (bit_index % 64);
    unsigned long *target = bitmap + (bit_index / 64);
    *target |= mask;
}