static __inline__ unsigned long atomic64_get_and_set(unsigned long *target, unsigned long value)
{
   return __atomic_get_and_set (target, &value, 5);
}