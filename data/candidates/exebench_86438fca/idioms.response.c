static __inline__ int atomic_sub(int *target, int o)
{
  int ret;
  __asm__ __volatile__(
    "lock ; " "xaddl %0, %1"
    :"=r" (ret), "=m" (*target) : "m" (*target) : "memory");
  return ret;
}