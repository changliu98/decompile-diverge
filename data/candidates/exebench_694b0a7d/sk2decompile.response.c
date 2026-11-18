static inline void dpaa_clear_bits(unsigned long mask,
                                   volatile unsigned long *addr) {
  unsigned long val;
  val = *addr;
  val &= ~mask;
  *addr = val;
}