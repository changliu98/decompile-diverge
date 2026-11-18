static inline long ihk_atomic_add_long_return(long a, long *target)
{
  __asm__ __volatile__(
    "lock ; " "xaddq %0, %1"
    : "=r" (a), "=m" (*target) : "m" (*target) : "memory");
  return a;
}