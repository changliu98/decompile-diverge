int func0(int* a, int n) {
  int i;
  int min = 0x80000000;
  for (i = 1; i < n; i++) {
    if (a[i] < min) return 0;
    if (a[i - 1] > min) min = a[i - 1];
  }
  return 1;
}