static __inline__ void xchg_add_64(unsigned long v, void *addr)
{
    __asm__ __volatile__(
        "lock xaddq %0, %1"
        :"=r"(v)
        :"m"(*((unsigned long *)addr))"m"(v));
}