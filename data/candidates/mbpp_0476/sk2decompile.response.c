int func0(int* a, int n) {
  int i;
  int max = 0x80000000;
  int min = 0x7fffffff;
  for (i = 0; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
    if (a[i] < min) {
      min = a[i];
    }
  }
  return max + min;
}