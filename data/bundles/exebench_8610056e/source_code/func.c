#include <asm/types.h>

static inline int test_and_set_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile("lock bts %2,%1\n\t"
       "sbb %0,%0" : "=r" (oldbit), "+m" (*(volatile long *) (addr))
       : "Ir" (nr) : "memory");

 return oldbit;
}
