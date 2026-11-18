int
atomicCompareAndSwap (int *addr, int old, int newval)
{
  int ret = old;
  __sync_lock_test_and_set (addr, newval);
  return ret;
}