int stb_combinations(int n, int k, int ***result) {
  int *a = (int *)calloc(k + 3, sizeof(int));
  int count = 0;
  int total = stb_factorial(n) / (stb_factorial(k) * stb_factorial(n - k));
  int **mat = stb_allocmat(total, k, sizeof(int));
  int i, j;
  for (i = 1; i <= k; ++i) a[i] = i - 1;
  a[k + 1] = n;
  a[k + 2] = 0;
  i = k;
  for (;;) {
    stb_visit(a, k, &mat, count++);
    while (i > 0) {
      a[i] = i;
      --i;
      stb_visit(a, k, &mat, count++);
    }
    while (a[1] + 1 < a[2]) {
      ++a[1];
      stb_visit(a, k, &mat, count++);
    }
    i = 2;
    a[1] = 0;
    j = a[2] + 1;
    while (j == a[i + 1]) {
      ++i;
      a[i - 1] = i - 2;
      j = a[i] + 1;
    }
    if (i > k) break;
    a[i] = j;
    --i;
  }
  *result = mat;
  free(a);
  return total;
}