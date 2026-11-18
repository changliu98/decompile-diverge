static __inline__ int atmc_fetch_and_add(int *var, int i) {
  int ret;
  __asm__ __volatile__(
    "lock ; " "xaddl %0, %1"
    : "=r" (ret), "=m" (*var) : "0" (i), "m" (*var) : "memory");
  return ret;
}