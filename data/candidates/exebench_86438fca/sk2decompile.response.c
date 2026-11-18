static inline void atomic_sub(int *v, int i) {
  int ret;
  ret = __sync_fetch_and_add((long *)v, -i);
  (void)ret;
}