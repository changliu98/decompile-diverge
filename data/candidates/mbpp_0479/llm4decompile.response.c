int func0(int n) {
  int i;
  for (i = n; i >= 10; i = i / 10) {
    n = i;
  }
  return n;
}