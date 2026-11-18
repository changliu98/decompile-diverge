static inline int atomic_sub(volatile int *i, int j) {
  return __sync_fetch_and_sub(i,j);
}