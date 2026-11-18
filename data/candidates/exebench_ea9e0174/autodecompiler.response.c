int
atomic_add (int *ptr, int val)
{
  return __sync_lock_test_and_set_4 (ptr, *ptr + val);
}