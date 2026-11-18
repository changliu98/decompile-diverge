static inline void atomic_clear_mask(unsigned long mask, unsigned long *p) {
  unsigned long val;
  val = *p;
  val &= ~mask;
  *p = val;
}