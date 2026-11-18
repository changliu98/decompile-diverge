unsigned long long int _binomial_coefficient(int n) {
  unsigned long long int **c;
  int i, j;
  unsigned long long int result;
  c = (unsigned long long int **)malloc((n + 1) * sizeof(unsigned long long int *));
  for (i = 0; i <= n; i++) {
    c[i] = (unsigned long long int *)malloc((n + 1) * sizeof(unsigned long long int));
    for (j = 0; j <= n; j++) {
      c[i][j] = 0;
    }
  }
  c[0][0] = 1;
  for (i = 1; i <= n; i++) {
    c[i][0] = c[i - 1][i - 1];
    for (j = 1; j <= i; j++) {
      c[i][j] = c[i][j - 1] + c[i - 1][j - 1];
    }
  }
  result = c[n][0];
  for (i = 0; i <= n; i++) {
    free(c[i]);
  }
  free(c);
  return result;
}