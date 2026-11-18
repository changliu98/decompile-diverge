static __inline__ void _hclib_atomic_dec_release(int *v)
{
   __asm__ __volatile__("lock; " "decl %0":"+m"(*v));
}