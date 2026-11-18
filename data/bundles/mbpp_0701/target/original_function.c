int func0(int arr[], int n) {
  int total_sum = 0;
  for (int i = 0; i < n; i++) {
    total_sum += arr[i];
  }
  int left_sum = 0;
  for (int i = 0; i < n; i++) {
    total_sum -= arr[i];
    if (left_sum == total_sum) {
      return i;
    }
    left_sum += arr[i];
  }
  return -1;
}