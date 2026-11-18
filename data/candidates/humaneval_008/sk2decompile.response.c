void func0(int *a, int n, int *b) {
  int i, sum, prod;
  sum = 0;
  prod = 1;
  for (i = 0; i < n; i++) {
    sum += a[i];
    prod *= a[i];
  }
  b[0] = sum;
  b[1] = prod;
}