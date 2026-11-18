int func0(int n, int b) {
  int p = 1;
  int i = 0;
  while (p <= n && i < 100) {
    if (p == n) return 1;
    p *= b;
    i++;
  }
  return 0;
}