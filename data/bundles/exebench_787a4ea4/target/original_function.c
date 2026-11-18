static inline int
atomic_add(volatile int *ptr, int incr)
{
  int r;
  asm volatile("lock; xaddl %0, %1" :
        "=r"(r), "=m"(*ptr) : "0" (incr), "m" (*ptr) : "memory");
  return r;
}