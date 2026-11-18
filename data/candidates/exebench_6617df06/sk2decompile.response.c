static inline int test_and_change_bit(int nr, volatile unsigned long *addr) {
  int retval;
  retval = (*addr & (1 << nr)) != 0;
  if (retval)
    *addr &= ~(1 << nr);
  else
    *addr |= (1 << nr);
  return retval;
}