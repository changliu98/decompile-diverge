static inline void atomic_add(int i, volatile int *v) {
  int ret;
  ret = __sync_fetch_and_add((int *)v, i);
  (void)ret;
}