int _maxSubArraySum(int *arr, int n) {
  int max_sum_left[n];
  for (int i = 0; i < n; i++) {
    max_sum_left[i] = arr[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] &&
          max_sum_left[i] < arr[i] + max_sum_left[j]) {
        max_sum_left[i] = arr[i] + max_sum_left[j];
      }
    }
  }
  int max_sum_right[n];
  for (int i = 0; i < n; i++) {
    max_sum_right[i] = arr[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[n - i - 1] > arr[n - j - 1] &&
          max_sum_right[n - i - 1] <
              arr[n - i - 1] + max_sum_right[n - j - 1]) {
        max_sum_right[n - i - 1] =
            arr[n - i - 1] + max_sum_right[n - j - 1];
      }
    }
  }
  int max_sum = -99999999;
  for (int i = 0; i < n; i++) {
    if (max_sum < max_sum_left[i] + max_sum_right[i] - arr[i]) {
      max_sum = max_sum_left[i] + max_sum_right[i] - arr[i];
    }
  }
  return max_sum;
}