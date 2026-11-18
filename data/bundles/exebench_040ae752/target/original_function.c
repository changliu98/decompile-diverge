static inline int
test_and_clear_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    __asm__ __volatile__(""
    "btrl %2,%1\n\tsbbl %0,%0":"=r"(oldbit),
    "=m"((*(volatile long *) addr)):"Ir"(nr):"memory");
    return oldbit;
}