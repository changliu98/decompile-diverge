void peneira(int n, int *A) {
  int i, j, x;
  i = 1;
  j = 2;
  x = A[i];
  while (j <= n) {
    if (j < n && A[j] < A[j + 1]) j++;
    if (x >= A[j]) break;
    A[i] = A[j];
    i = j;
    j *= 2;
  }
  A[i] = x;
}