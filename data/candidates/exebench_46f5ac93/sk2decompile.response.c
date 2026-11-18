static inline void spin_unlock(int *lock) {
  unsigned char zero = 0;
  asm volatile("movb %%al, %0" : "=m"(zero) : : "eax");
  *lock = zero;
}