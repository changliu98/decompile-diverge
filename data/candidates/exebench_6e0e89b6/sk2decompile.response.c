static inline void clear_bit(int nr, unsigned long *addr) {
  unsigned long *p = addr + (nr >> 6);
  unsigned long mask = 1UL << (nr & 0x3f);
  *p &= ~mask;
}