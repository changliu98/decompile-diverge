static __inline__ void p_atomic_dec(int *v)
{
   __asm__ __volatile__("lock; " "decl %0":"+m"(*v));
}