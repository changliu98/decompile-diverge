static inline int xchg(int *m, int val) {
  int ret;
  ret = __sync_lock_test_and_set((long *)m, val);
  return ret;
}