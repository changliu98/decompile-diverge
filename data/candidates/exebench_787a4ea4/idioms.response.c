static __inline__ int atomic_add(int *var, int v) {
  return __sync_fetch_and_add(var, v);
}