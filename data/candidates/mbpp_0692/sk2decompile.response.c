int func0(int n) {
  int i, j;
  if (n >= 10) return 0;
  j = 1;
  for (i = 1; i <= n; i++) {
    j = (j * i) % 100;
  }
  return j;
}