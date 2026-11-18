int func0(int a, int b) {
  int ret = 1;
  int i;
  if (a == b) return 1;
  if (b - a >= 5) return 0;
  for (i = a + 1; i <= b; i++) {
    ret = (ret % 10) * (i % 10);
  }
  return ret % 10;
}