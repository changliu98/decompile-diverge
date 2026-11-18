static inline void generic_set_bit(int nr, volatile unsigned long *addr) {
  unsigned long *a = addr + nr / 32;
  unsigned long mask = 1UL << (nr % 32);
  *a |= mask;
}