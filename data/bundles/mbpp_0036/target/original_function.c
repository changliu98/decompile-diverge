int func0(int p, int q, int N) {
  int res;
  while (N > 0) {
    N--;
    p *= 10;
    res = p / q;
    p = p % q;
  }
  return res;
}