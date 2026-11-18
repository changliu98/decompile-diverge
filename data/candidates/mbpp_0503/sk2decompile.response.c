void func0(int* a, int n, int* b) {
  int i;
  for (i = 0; i < n - 1; i++) {
    b[i] = a[i] + a[i + 1];
  }
}