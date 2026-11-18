static inline void clear_bit(int nr, volatile void *addr) {
  unsigned long tmp;
  tmp = *(unsigned long *)addr;
  tmp &= ~(1 << nr);
  *(unsigned long *)addr = tmp;
}