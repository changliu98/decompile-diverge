static inline void sync_set_bit(int nr, volatile unsigned long *addr)
{
 asm volatile("lock; btsl %1,%0"
       : "+m" ((*(volatile long *)addr))
       : "Ir" (nr)
       : "memory");
}