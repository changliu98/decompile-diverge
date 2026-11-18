static __inline__ int atomic_inc(int *cnt)
{
  int ret;
  __asm__ __volatile__ (
  "lock ; " "incl %0"
  :"=m" (*cnt)
  :"m" (*cnt));
  return *cnt;
}