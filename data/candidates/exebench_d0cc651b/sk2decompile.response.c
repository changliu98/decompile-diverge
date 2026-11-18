void increment(unsigned *x) {
  unsigned mask, y;
  y = *x;
  mask = 1;
  while (y & mask) {
    y ^= mask;
    mask <<= 1;
  }
  y ^= mask;
  *x = y;
}