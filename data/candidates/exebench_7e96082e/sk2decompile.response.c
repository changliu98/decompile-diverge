static inline void atomic_dec(int *v) {
  int ret;
  ret = __sync_sub_and_fetch((long *)v);
  (void)ret;
}