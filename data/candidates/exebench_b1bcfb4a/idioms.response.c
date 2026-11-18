static __inline__ void dpaa_set_bits(unsigned long v, void *addr)
{
    __asm__ __volatile__(
        "lock xaddq %0, %1"
        :"=r"(v)
        :"m"(*((unsigned long *)addr))"m"(v));
}