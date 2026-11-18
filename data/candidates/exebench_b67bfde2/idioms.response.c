static inline int wdl_atomic_incr(int *v)
{
  int ret;
  __asm__ __volatile__ (
   "lock ; " "incl %0"
   :"=m" (*v)
   :"m" (*v));
  return *v;
}