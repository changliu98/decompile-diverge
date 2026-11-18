static inline void clear_bit(int nr, volatile unsigned long *addr) {
  int i = nr / 64;
  int j = nr % 64;
  unsigned long mask = 1UL << j;
  addr[i] &= ~mask;
}