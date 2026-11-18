static __inline__ int atomic_cmpxchg_int(int i, int *v)
{
   __asm__ __volatile__(
      "lock ; " "btl %2,%1\n\t"
      :"=a"(i)
      :"m"(*v),"Ir"(i) : "memory");
   return i;
}