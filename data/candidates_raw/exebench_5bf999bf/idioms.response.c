static __inline__ void futex_clear(int nr, struct futex *fu)
{
    __asm__ __volatile__ (
        "lock btrl %1,%0"
        :"=m" (fu->lock)
        :"Ir" (nr));
}