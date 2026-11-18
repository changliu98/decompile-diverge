int func0(int *arr, int n) {
  int i, even = -1, odd = -1;
  for (i = 0; i < n; i++) {
    if (arr[i] % 2 == 0 && even == -1) even = arr[i];
    if (arr[i] % 2 != 0 && odd == -1) odd = arr[i];
    if (even != -1 && odd != -1) break;
  }
  return even * odd;
}