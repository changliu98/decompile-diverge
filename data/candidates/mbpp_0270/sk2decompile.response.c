int func0(int *arr, int len) {
  int i, sum = 0;
  for (i = 0; i < len; i += 2) {
    if (arr[i] % 2 == 0) sum += arr[i];
  }
  return sum;
}