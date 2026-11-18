static inline int test_and_set_bit(int nr, volatile unsigned long *addr) {
  int ret;
  ret = -__test_and_set_bit((int *)addr, nr);
  return ret;
}