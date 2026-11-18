static inline void do_cpuid(unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d)
{
  __asm__ __volatile__ (
  "cpuid"
  :"=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
  :"0"(*a));
}