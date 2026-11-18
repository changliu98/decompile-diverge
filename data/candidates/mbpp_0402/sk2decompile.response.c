int _binomial_coefficient(int n, int k, int mod) {
  int i, j, min;
  int C[k + 1];
  for (j = 0; j <= k; j++) C[j] = 0;
  C[0] = 1;
  for (i = 1; i <= n; i++) {
    if (i < k)
      min = i;
    else
      min = k;
    for (j = min; j > 0; j--) C[j] = (C[j] + C[j - 1]) % mod;
  }
  return C[k];
}