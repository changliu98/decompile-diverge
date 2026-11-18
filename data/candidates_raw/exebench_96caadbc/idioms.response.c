static inline long atomic64_add_int(long a, long *target)
{
  __asm__ __volatile__(
    "lock ; " "xaddq %0, %1"
    : "=r" (a), "=m" (*target) : "m" (*target) : "memory");
  return a;
}