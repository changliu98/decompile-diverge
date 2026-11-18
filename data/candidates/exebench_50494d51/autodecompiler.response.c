void set_bit(int bit, long *bitvec) {
 long mask = 1L << (bit % 64);
 long *ptr = bitvec + (bit / 64);
 *ptr &= ~mask;
}