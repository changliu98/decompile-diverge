static inline void atomic_and(unsigned long long *v, unsigned long long andv) {
  unsigned long long new, old;
  new = *v;
  do {
    old = new;
    new = andv & old;
  } while (
      !__sync_bool_compare_and_swap((long long volatile *)v, (long long)old,
                                    (long long)new));
}