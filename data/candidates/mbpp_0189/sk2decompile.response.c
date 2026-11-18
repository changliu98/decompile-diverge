int _find_first_missing_positive(int *A, int n) {
  int has_one = 0;
  int i;
  for (i = 0; i < n; i++) {
    if (A[i] == 1) {
      has_one = 1;
      break;
    }
  }
  if (has_one == 0) return 1;
  for (i = 0; i < n; i++) {
    if (A[i] <= 0 || A[i] > n) A[i] = 1;
  }
  for (i = 0; i < n; i++) {
    A[(A[i] - 1) % n] += n;
  }
  for (i = 0; i < n; i++) {
    if (A[i] <= n) return i + 1;
  }
  return n + 1;
}