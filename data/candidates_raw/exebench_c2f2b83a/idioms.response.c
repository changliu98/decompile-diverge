static __inline__ void p_enter(struct p *p)
{
  __asm__ __volatile__ (
    "lock ; incl %0":"+m"(*(p))
  );
}