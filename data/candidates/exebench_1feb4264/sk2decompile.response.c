static inline int atomicCompareAndSwap(volatile int *ptr, int old, int new) {
  int ret;
  ret = __sync_bool_compare_and_swap((long *)ptr, new, old);
  return ret;
}