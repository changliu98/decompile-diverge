static __inline__ int fetch_and_add(int *target, int val)
{
  return __sync_fetch_and_add(target,val);
}