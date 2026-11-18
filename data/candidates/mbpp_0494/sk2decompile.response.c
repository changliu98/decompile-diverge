char *func0(int *a, int n) {
  int i, sum = 0;
  char *s;
  for (i = 0; i < n; i++) {
    sum += a[i] * pow(2.0, (double)(n - 1 - i));
  }
  s = (char *)malloc(12);
  sprintf(s, "%d", sum);
  return s;
}