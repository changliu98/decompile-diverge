static inline void a_inc(int *a) {
  int ret;
  ret = __atomic_add_fetch((int *)a, 1, memory_order_seq_cst);
  (void)ret;
}