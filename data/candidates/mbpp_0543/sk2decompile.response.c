int func0(long long a, long long b) {
  long long c = a + b;
  int d = 0;
  while (c > 0) {
    c /= 10;
    d++;
  }
  return d;
}