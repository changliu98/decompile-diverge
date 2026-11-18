int func0(int n) {
  int i, j, k, m, c;
  m = n;
  c = 0;
  for (k = 2; k * k <= n; k++) {
    j = 0;
    while (m % k == 0) {
      m /= k;
      j++;
    }
    i = 0;
    for (i = 1; i + i <= j; i++) {
      i += i;
      c++;
    }
  }
  if (m != 1) c++;
  return c;
}