int func0(int n) {
  int i, c;
  int m = n;
  if (n < 2) return 0;
  c = 0;
  for (i = 2; i * i <= m; i++) {
    while (m % i == 0) {
      m /= i;
      c++;
    }
  }
  if (m > 1) c++;
  return c == 3;
}