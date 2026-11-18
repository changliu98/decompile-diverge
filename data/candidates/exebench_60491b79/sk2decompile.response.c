static inline int sync_test_and_set_bit(int nr, volatile unsigned long *addr) {
  int ret;
  ret = -(__test_and_set_bit((long *)addr, nr) & 1);
  return ret;
}