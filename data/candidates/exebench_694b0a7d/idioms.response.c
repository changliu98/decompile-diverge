static __inline__ void dpaa_clear_bits(void *ptr, void *val)
{
  __asm__ __volatile__("xchgl %0,%1"
   :"=r" (val) : "m" (*((long *)ptr)) : "memory");
}