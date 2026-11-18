static inline int atomic_add32_ret(int *ptr) {
  int ret;
  ret = __sync_add_and_fetch((int *)ptr, 1);
  return ret;
}