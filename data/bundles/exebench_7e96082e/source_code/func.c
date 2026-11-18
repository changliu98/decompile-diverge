
static __inline__ void atomic_dec(volatile int *v)
{
        __asm__ __volatile__(
                "lock; decl %0"
                :"=m" (*v)
                :"m" (*v));
}
