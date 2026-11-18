unsigned long gf32_mod(unsigned long a, int n) {
  while (n >= 32) {
    if (a & (1UL << n)) {
      a ^= (0x1f273645UL << (n - 32));
    }
    n--;
  }
  return a;
}