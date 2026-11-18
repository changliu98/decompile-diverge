int func0(int n, int m, int r) {
  int i, max = 0x80000000;
  for (i = 0; i <= n; i++) {
    if (i % m == r && i > max) max = i;
  }
  if (max >= 0 && max <= n)
    return max;
  else
    return -1;
}