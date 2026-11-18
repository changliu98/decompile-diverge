int func0(int *arr, int len) {
  int i, sum = 0;
  for (i = 0; i * 2 < len; i++) {
    if (arr[i * 2] % 2 == 1) {
      sum += arr[i * 2];
    }
  }
  return sum;
}