static inline intptr_t atomic_fetch_and(volatile intptr_t *ptr, intptr_t val) {
  intptr_t old = *ptr;
  *ptr = old & val;
  return old;
}