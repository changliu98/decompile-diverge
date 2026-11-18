static inline intptr_t atomic_fetch_add(volatile intptr_t *ptr, intptr_t val) {
  intptr_t old = *ptr;
  *ptr += val;
  return old;
}