int func0(int *arr, int n) {
  int i, even, odd;
  even = -1;
  odd = -1;
  for (i = 0; i < n; i++) {
    if (arr[i] % 2 == 0) {
      even = arr[i];
      break;
    }
  }
  for (i = 0; i < n; i++) {
    if (arr[i] % 2 != 0) {
      odd = arr[i];
      break;
    }
  }
  return even + odd;
}