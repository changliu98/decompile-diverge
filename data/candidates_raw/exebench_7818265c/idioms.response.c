static __inline__ int atomic_int_exchange(int *target, int value)
{
  return __sync_lock_test_and_set(target, value);
}