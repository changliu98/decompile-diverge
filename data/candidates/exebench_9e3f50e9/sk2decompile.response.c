void AddArray4(float *a, float *b, int n) {
  int i;
  for (i = 0; i < n; i += 4) {
    b[i] += a[i];
    b[i + 1] += a[i + 1];
    b[i + 2] += a[i + 2];
    b[i + 3] += a[i + 3];
  }
}