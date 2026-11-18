int func0(int *arr, int n) {
  int i, j, even, odd;
  even = -1;
  odd = -1;
  for (i = 0; i < n; i++) {
    if (arr[i] % 2 == 0) {
      even = arr[i];
      break;
    }
  }
  for (j = 0; j < n; j++) {
    if (arr[j] % 2 != 0) {
      odd = arr[j];
      break;
    }
  }
  return even - odd;
}