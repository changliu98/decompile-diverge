void set_bit(int bit, unsigned long *ptr) {
    ptr[bit / 8] |= (1UL << (bit % 8));
}