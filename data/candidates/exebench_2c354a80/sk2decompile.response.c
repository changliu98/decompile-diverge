static inline void entry_clr_protected(unsigned long *entry) {
  *entry &= ~(1UL << 9);
  *entry &= ~(1UL << 9);
}