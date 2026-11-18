static inline void set_bit(int nr, volatile void *addr) {
  unsigned long *a = (unsigned long *)addr;
  unsigned long mask = 1UL << nr;
  asm volatile("bts %2,%1\n\t" : "=m"(a[0]) : "r"(a[0]), "Ir"(mask));
}