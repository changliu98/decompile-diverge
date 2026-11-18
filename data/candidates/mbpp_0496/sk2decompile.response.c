void func0(int* a, int n, int k, int* out) {
  qsort(a, n, sizeof(int), cmpfunc);
  for (int i = 0; i < k; i++) {
    out[i] = a[i];
  }
}