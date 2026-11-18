static __inline__ void atomicDecrement(int *v)
{
   __asm__ __volatile__("lock; decl %0":"+m"(*v));
}