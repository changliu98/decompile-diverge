static __inline__ void atomic_inc(struct p *p)
{
  __asm__ __volatile__ (
  "lock ; incl %0":"+m"(*(p)->lock)
  );
}