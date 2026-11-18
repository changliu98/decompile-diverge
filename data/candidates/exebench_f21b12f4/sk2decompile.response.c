static inline void nm_writel(unsigned int val, unsigned int *addr) {
  unsigned int tmp;
  tmp = val;
  *addr = tmp;
}