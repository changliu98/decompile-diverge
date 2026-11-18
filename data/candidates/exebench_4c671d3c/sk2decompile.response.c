void standardize(long n, long *a, long *b, long *c, long *A, long *B, long *C) {
  long i;
  for (i = 0; i < 3; i++) {
    if (i < n) {
      a[i] = A[i];
      b[i] = B[i];
      c[i] = C[i];
    } else {
      a[i] = 0;
      b[i] = 1;
      c[i] = 1;
    }
  }
}