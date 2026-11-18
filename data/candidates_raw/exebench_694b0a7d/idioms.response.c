static __inline__ void xchg(void *ptr, void *val)
{
  __asm__ __volatile__("xchgl %0,%1"
   :"=r" (val) : "m" (*((long *)ptr)) : "memory");
}