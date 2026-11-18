static inline int sync_test_and_change_bit(int nr, volatile unsigned long *addr) {
  int ret;
  asm volatile("lock; btc %1,%0"
               : "=m"(*addr), "=r"(ret)
               : "0"(addr), "1"(nr));
  return ret;
}