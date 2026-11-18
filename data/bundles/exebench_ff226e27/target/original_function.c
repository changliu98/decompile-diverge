static __inline__ void atomic_add(int i, volatile long *v)
{
        __asm__ __volatile__(
                "lock; addl %1,%0"
                :"=m" (*v)
                :"ir" (i), "m" (*v));
}