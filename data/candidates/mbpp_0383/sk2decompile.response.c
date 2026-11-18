int func0(int n) {
  int m = n;
  int mask = 0;
  int i = 0;
  while (m > 0) {
    if (i % 2 == 0) {
      mask |= 1 << i;
    }
    i++;
    m >>= 1;
  }
  return n ^ mask;
}