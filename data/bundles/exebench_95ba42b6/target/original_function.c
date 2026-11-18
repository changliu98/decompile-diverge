static __inline__ void atomic_inc(volatile int *v)
{
        __asm__ __volatile__(
               "lock; incl %0"
                :"=m" (*v)
                :"m" (*v));
}