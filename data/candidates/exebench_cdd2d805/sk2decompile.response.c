static inline void atomic_retain(int *value) {
  int old;
  old = __sync_fetch_and_add((int *)value, 1);
  (void)old;
}