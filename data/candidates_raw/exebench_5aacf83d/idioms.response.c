static __inline__ int atomic_get_and_set(int *var, int v) {
  return __sync_lock_test_and_set(var, v);
}