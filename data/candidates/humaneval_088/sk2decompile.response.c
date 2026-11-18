void func0(int *a, int n, int **b, int *m) {
  *m = n;
  if (n == 0) {
    *b = NULL;
    return;
  }
  *b = malloc(n * sizeof(int));
  if (*b == NULL) {
    exit(1);
  }
  int i;
  for (i = 0; i < n; i++) {
    (*b)[i] = a[i];
  }
  int odd = (a[0] + a[n - 1]) % 2 == 1;
  int j, k;
  for (j = 0; j < n - 1; j++) {
    for (k = j + 1; k < n; k++) {
      if (odd) {
        if ((*b)[j] > (*b)[k]) {
          int tmp = (*b)[j];
          (*b)[j] = (*b)[k];
          (*b)[k] = tmp;
        }
      } else {
        if ((*b)[j] < (*b)[k]) {
          int tmp = (*b)[j];
          (*b)[j] = (*b)[k];
          (*b)[k] = tmp;
        }
      }
    }
  }
}