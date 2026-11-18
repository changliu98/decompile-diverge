static __inline__ int atomic_add_int(int *target, int val)
{
  return __sync_fetch_and_add(target,val);
}