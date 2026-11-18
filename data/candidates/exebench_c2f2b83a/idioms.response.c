static __inline__ void a_inc(struct p *p)
{
  __asm__ __volatile__ (
    "lock ; incl %0":"+m"(*(p))
  );
}