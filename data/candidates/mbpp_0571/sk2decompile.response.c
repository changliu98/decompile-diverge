int func0(int *arr, int size, int k) {
  qsort(arr, size, sizeof(int), cmp);
  int *dp = malloc(size * sizeof(int));
  dp[0] = 0;
  for (int i = 1; i < size; i++) {
    dp[i] = dp[i - 1];
    if (arr[i] - arr[i - 1] < k) {
      if (i >= 2) {
        dp[i] = (dp[i] > arr[i - 1] + arr[i] + dp[i - 2])
                    ? dp[i]
                    : arr[i - 1] + arr[i] + dp[i - 2];
      } else {
        dp[i] = (dp[i] > arr[i - 1] + arr[i]) ? dp[i] : arr[i - 1] + arr[i];
      }
    }
  }
  int ret = dp[size - 1];
  free(dp);
  return ret;
}