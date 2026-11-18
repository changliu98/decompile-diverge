int func0(int *A, int N, int K) {
  int min = N - 1;
  qsort(A, N, sizeof(int), (int (*)(const void *, const void *))func1);
  for (int i = 0; i < N; i++) {
    int ind = find_ind(A[i], i, N, K, A);
    if (ind != -1) {
      min = min < N - (ind - i + 1) ? min : N - (ind - i + 1);
    }
  }
  return min;
}