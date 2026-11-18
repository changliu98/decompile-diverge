static __inline__ void atomic_retain(int *v)
{
   __asm__ __volatile__("lock ; incl %0":"+m"(*v));
}