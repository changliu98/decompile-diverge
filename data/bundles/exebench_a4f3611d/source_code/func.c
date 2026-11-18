
static inline int sync_test_and_change_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile("lock; btcl %2,%1\n\tsbbl %0,%0"
       : "=r" (oldbit), "+m" ((*(volatile long *)addr))
       : "Ir" (nr) : "memory");
 return oldbit;
}
