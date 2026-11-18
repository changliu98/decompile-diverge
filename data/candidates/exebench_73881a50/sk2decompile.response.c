static inline int test_and_set_bit(int nr, volatile unsigned long *addr) {
  int retval;
  retval = -((*addr) & (1 << nr));
  (*addr) |= (1 << nr);
  return retval;
}