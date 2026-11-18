int func0(int *a, int n) {
  int i, j, c, sum;
  sum = 0;
  for (j = 0; j < n; j++) {
    c = 1;
    for (i = 0; i < n; i++) {
      if (a[i] == a[j] && i != j) c++;
    }
    if (c > 1) sum += a[j];
  }
  return sum;
}