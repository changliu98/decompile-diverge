static inline void clear_bit(int nr, volatile unsigned long *addr)
{
 unsigned long mask = (1UL << ((nr) % ((int)sizeof(unsigned long)*8)));
 unsigned long *p = ((unsigned long *)addr) + ((nr) / ((int)sizeof(unsigned long)*8));

 *p &= ~mask;
}