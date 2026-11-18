

static inline int
test_and_set_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    __asm__ __volatile__(""
    "btsl %2,%1\n\tsbbl %0,%0":"=r"(oldbit),
    "=m"((*(volatile long *) addr)):"Ir"(nr):"memory");
    return oldbit;
}
