void set_bit(int bit, unsigned long *array) {
    array[bit / 64] |= (1UL << (bit % 64));
}