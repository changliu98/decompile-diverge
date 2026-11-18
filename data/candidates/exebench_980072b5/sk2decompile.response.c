static inline void set_bit(int nr, volatile unsigned long *addr) {
  unsigned long *p = addr + nr / 64;
  int bit = nr % 64;
  *p |= 1UL << bit;
}