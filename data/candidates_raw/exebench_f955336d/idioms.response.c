static __inline__ int atomic_int_add(int *target, int val)
{
  int ret;
  __asm__ __volatile__ (
    "lock ; " "xaddl %0, %1"
    :"=r"(ret), "=m"(*target)
    :"m"(*target), "0"(val)
    :"memory"
  );
  return ret;
}