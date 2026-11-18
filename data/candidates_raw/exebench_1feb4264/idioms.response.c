static __inline__ int atomic_cmpxchg_int(int *var, int old, int new_v)
{
   int ret;
   __asm__ __volatile__(
      "lock ; " "cmpxchgl %2, %1"
      : "=a"(ret), "=m"(*var)
      : "r"(new_v), "m"(*var), "0"(old)
      : "cc", "memory"
   );
   return ret;
}