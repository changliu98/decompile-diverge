static __inline__ int xchg(int *target, int value)
{
  return __sync_lock_test_and_set(target, value);
}