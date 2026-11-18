void clear_bit(int bit, unsigned long *map) {
    map[bit / INT_SIZE] &= ~(1L << (bit % INT_SIZE));
}