static __inline__ void a_inc(int *v)
{
   __asm__ __volatile__("lock ; incl %0":"+m"(*v));
}