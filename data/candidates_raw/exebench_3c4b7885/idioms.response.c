static __inline__ void bitset(int nr, void *addr)
{
    __asm__ __volatile__(
        "lock btest %k0,%1\n\t"
        "jnz 1f\n\t"
        "lock bts %k0,%1\n\t"
        "1:\n\t"
        :"=m"((unsigned long)nr), "=m"(((unsigned long *)addr)[0])
        :"0"(nr)
        :"memory");
}