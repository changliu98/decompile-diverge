static __inline__ void ff_atomic_dec_long(struct atomic_t *v)
{
   __asm__ __volatile__ (
      "lock ; " "decq %0"
      :"=m" (v->counter)
      :"m" (v->counter));
}