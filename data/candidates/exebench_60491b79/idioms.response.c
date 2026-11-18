static __inline__ int sync_test_and_set_bit(int nr, int *addr)
{
  int oldbit;
  __asm__ __volatile__ (
  "lock btestb %1,%0\n\t"
  "setz %2\n\t"
  :"=m" (*addr), "=m" (addr[nr]), "=a" (oldbit)
  :"0" (*addr), "m" (addr[nr])
  :"memory");
  return oldbit;
}