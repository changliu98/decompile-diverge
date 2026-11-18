static inline void a_swap(int *a, int n) {
  int ret;
  ret = __builtin_a_swap((int *)a, n);
  (void)ret;
}