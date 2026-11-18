void func0(int* a, int* b, int n) {
  int i;
  for (i = 0; i < n; i++) {
    b[i] = a[i] * a[i];
  }
}