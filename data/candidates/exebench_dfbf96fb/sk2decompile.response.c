static inline int a_swap(int *ptr, int val) {
  int old, tmp;
  do {
    old = *ptr;
    tmp = *ptr;
  } while (__sync_val_compare_and_swap(ptr, val, tmp) != tmp);
  return old;
}