static __inline__ void p_atomic_inc(int *v)
{
   __asm__ __volatile__("lock ; incl %0":"+m"(*v));
}