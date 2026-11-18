static __inline__ int test_and_change_bit(int i, int *target)
{
   int ret;
   __asm__ __volatile__(
      "lock ; " "cmpxchgl %0, %1"
      : "=a"(ret), "=m"(*target) : "0"(i), "m"(*target) : "memory");
   return ret;
}