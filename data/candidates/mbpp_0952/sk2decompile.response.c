int func0(int n, int k, int m) {
  if (k > n - k) k = n - k;
  int c[k + 1];
  int i, j, min;
  for (i = 0; i <= k; i++) c[i] = 0;
  c[0] = 1;
  for (i = 1; i <= n; i++) {
    if (i < k)
      min = i;
    else
      min = k;
    for (j = min; j > 0; j--) c[j] = (c[j] + c[j - 1]) % m;
  }
  return c[k];
}