static inline void set_bit(int nr, unsigned long *addr) {
  unsigned long *p = addr + (nr >> 6);
  unsigned long mask = 1UL << (nr & 63);
  *p |= mask;
}