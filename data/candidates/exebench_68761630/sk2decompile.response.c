static inline void a_or(int *a, int b) {
  int ret;
  ret = __atomic_or_fetch((int *)a, b, memory_order_seq_cst);
  (void)ret;
}