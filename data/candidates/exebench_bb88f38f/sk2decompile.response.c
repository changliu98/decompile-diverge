static inline void sync_clear_bit(int nr, volatile unsigned long *addr) {
  unsigned long flags;
  flags = __sync_lock_test_and_set_bit((unsigned long *)addr, nr);
  (void)flags;
}