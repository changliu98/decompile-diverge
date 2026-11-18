static __inline__ unsigned long AddUintptr(unsigned long *target, unsigned long value)
{
  return __sync_fetch_and_add(target, value) + value;
}