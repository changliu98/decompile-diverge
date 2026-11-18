static __inline__ int atomic_add_int(int *var, int v) {
  int ret;
  __asm__ __volatile__(
      "lock ; " "xaddl %0, %1"
      :"=r"(ret), "=m"(*var)
      :"m"(*var), "0"(v));
  return ret;
}