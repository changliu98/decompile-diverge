static __inline__ void clear_bit(int nr, struct futex *fu)
{
    __asm__ __volatile__ (
        "lock btrl %1,%0"
        :"=m" (fu->lock)
        :"Ir" (nr));
}