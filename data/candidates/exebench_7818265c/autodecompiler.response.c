int
xchg (int *ptr, int val)
{
  int oldval;

  __asm__ __volatile__ ("lock\n\t" "xchg %2,%1"
                        : "=r" (oldval), "+m" (*ptr)
                        : "r" (val)
                        : "memory");

  return oldval;
}