static __inline__ void sync_clear_bit(int nr, void *addr)
{
   __asm__ __volatile__ (
   "lock btrl %1,%0"
   :"=m"((*(long *)addr))
   :"Ir"(nr));
}