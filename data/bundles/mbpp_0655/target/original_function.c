int func0(int n) {
  int sm = 0;
  for (int i = 1; i <= n; i++) {
    sm += i * i * i * i * i;
  }
  return sm;
}