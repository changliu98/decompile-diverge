

static inline void
clear_bit(int nr, volatile unsigned long *addr)
{
    __asm__ __volatile__("" "btrl %1,%0":"=m"((*(volatile long *) addr)):"Ir"(nr));
}
