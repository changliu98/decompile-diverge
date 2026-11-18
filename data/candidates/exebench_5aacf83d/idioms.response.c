static __inline__ int a_swap(int *var, int v) {
  return __sync_lock_test_and_set(var, v);
}