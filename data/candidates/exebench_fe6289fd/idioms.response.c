static __inline__ unsigned long xchg8(unsigned long *target, unsigned long value)
{
   return __atomic_get_and_set (target, &value, 5);
}