static __inline__ int atomic_bittestandset(int nr, int *addr)
{
    int oldbit;
    __asm__ __volatile__(
        "lock btest %1,%0\n\t"
        "setz %2\n\t"
        :"=m"(*addr), "=m"(*(addr + 1)), "=a"(oldbit)
        :"0"(*addr), "1"(nr)
        :"memory");
    return oldbit;
}