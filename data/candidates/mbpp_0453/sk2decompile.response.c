int func0(int n) {
  int i, j, k, p, m;
  m = n;
  if (n % 2) return 0;
  p = 1;
  for (i = 2; i <= sqrt((double)m) + 1; i++) {
    j = 0;
    k = 1;
    p = 1;
    while (m % i == 0) {
      j++;
      m /= i;
      if (i == 2 && j == 1) k = 0;
      p *= i;
      k += p;
    }
    p *= k;
  }
  if (m >= 2) p *= m + 1;
  return p;
}