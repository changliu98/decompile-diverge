static inline void atomic_or_long(long *v, unsigned long d) {
  unsigned long tmp;
  tmp = *(unsigned long *)v;
  tmp |= d;
  *(unsigned long *)v = tmp;
}