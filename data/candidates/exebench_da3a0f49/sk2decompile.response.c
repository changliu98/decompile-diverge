static inline int test_and_change_bit(int nr, volatile unsigned long *addr) {
  unsigned long mask;
  mask = (1UL << (nr & 63));
  if (*addr & mask) {
    return 1;
  }
  *addr |= mask;
  return 0;
}