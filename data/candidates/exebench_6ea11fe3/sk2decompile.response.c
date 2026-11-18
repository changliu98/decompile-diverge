static inline void sync_set_bit(int nr, volatile unsigned long *addr) {
  int tmp;
  asm volatile(
      "lock; bts %1, %0"
      : "+m"(*addr), "=a"(tmp)
      : "Ir"(nr));
}