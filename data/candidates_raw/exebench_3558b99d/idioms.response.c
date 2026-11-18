static __inline__ void atomic_dec(struct atomic_t *v)
{
   __asm__ __volatile__ (
      "lock ; " "decq %0"
      :"=m" (v->counter)
      :"m" (v->counter));
}