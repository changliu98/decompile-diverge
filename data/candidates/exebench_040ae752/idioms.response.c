static __inline__ int test_and_clear_bit(int i, int *v)
{
   __asm__ __volatile__(
      "lock ; " "btri %2,%1\n\t"
      :"=a"(i)
      :"m"(*v),"Ir"(i)
      :"memory"
   );
   return i;
}