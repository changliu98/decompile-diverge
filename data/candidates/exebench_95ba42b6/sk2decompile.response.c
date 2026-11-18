static inline void atomic_inc(int *v) {
  int ret;
  ret = __sync_add_and_fetch((long *)v, 1);
  (void)ret;
}