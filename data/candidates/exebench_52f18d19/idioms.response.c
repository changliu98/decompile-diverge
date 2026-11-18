static __inline__ int atomicIncrement(int *var)
{
  int ret;
  __asm__ __volatile__(
   "lock ; " "incl %0"
   :"=m" (ret)
   :"m" (*var));
  return ret;
}