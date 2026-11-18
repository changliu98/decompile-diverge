static inline void atomic_inc(int *v) {
  int ret;
  ret = __sync_add_and_fetch((int *)v);
  (void)ret;
}