

static inline void
set_bit(int nr, volatile unsigned long *addr)
{
    __asm__ __volatile__("" "btsl %1,%0":"=m"((*(volatile long *) addr)):"Ir"(nr));
}
