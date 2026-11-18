static inline void sync_clear_bit(int nr, volatile unsigned long *addr)
{
 asm volatile("lock; btrl %1,%0"
       : "+m" ((*(volatile long *)addr))
       : "Ir" (nr)
       : "memory");
}