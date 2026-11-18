long func0(int n) {
  int i;
  long f = 1, s = 1;
  for (i = 1; i <= n; i++) {
    f *= i;
    s *= f;
  }
  return s;
}