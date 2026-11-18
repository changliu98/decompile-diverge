void set_bit(unsigned int *x, int bit) {
  unsigned int mask = 1;
  mask <<= bit;
  *x |= mask;
}