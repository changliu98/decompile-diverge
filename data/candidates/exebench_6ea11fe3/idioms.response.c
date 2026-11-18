static __inline__ void sync_set_bit(int nr, void *addr)
{
   __asm__ __volatile__ (
      "lock btl %1,%0":"+m"((*(unsigned long long *)addr)) : "Ir"(nr) : "memory");
}