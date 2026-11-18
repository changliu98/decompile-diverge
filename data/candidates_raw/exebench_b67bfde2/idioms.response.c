static inline int atomic_inc(int *v)
{
  int ret;
  __asm__ __volatile__ (
   "lock ; " "incl %0"
   :"=m" (*v)
   :"m" (*v));
  return *v;
}