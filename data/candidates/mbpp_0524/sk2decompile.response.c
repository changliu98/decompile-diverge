int func0(int *arr, int size) {
  int max = 0;
  int sum[size];
  for (int i = 0; i < size; i++) {
    sum[i] = arr[i];
  }
  for (int i = 1; i < size; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && sum[i] < sum[j] + arr[i]) {
        sum[i] = sum[j] + arr[i];
      }
    }
  }
  for (int i = 0; i < size; i++) {
    if (sum[i] > max) {
      max = sum[i];
    }
  }
  return max;
}