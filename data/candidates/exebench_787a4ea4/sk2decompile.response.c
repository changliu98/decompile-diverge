static inline void atomic_add(int *v, int n) {
  int ret;
  ret = __sync_add_and_fetch((long *)v, n);
}