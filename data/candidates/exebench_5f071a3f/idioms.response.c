static __inline__ void StoreUintptr(int *target, int value)
{
  int old;
  __asm__ __volatile__ (
    "1:\tll %0,%1\n\t"
    "sc %0,%2\n\t"
    "jnz 1b"
    :"=r"(old), "=m"(*target)
    :"m"(*target), "r"(value));
}