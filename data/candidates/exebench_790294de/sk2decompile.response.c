void atomic_or(unsigned int *p, unsigned int v) {
  unsigned int new, old;
  new = *p;
  do {
    old = new;
    new = old | v;
  } while (!__sync_bool_compare_and_swap((long long *)p, (long long)old,
                                         (long long)new));
}