static __inline__ unsigned long atomic_add_uint64(unsigned long *target, unsigned long value)
{
  return __sync_fetch_and_add(target, value) + value;
}