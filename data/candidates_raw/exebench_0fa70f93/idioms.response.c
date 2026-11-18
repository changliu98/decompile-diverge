void clear_bit(unsigned long bit, void *addr)
{
  __asm__ __volatile__ (
  "andl %0, %1"
  :"=r" (bit)
  :"m" (*(long *)addr)
  );
}