static inline int
atomic_add32_ret(int *cnt)
{
    int __c = 1;

    __asm__ __volatile("lock; xadd %0,%1":"+r"(__c), "+m"(*cnt)::"memory");




    return __c;
}