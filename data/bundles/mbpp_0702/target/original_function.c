int func0(int arr[], int n, int k) {
  int ans = n - 1;
  qsort(arr, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
  for (int i = 0; i < n; i++) {
    int j = find_ind(arr[i], i, n, k, arr);
    if (j != -1) {
      ans = (ans < n - (j - i + 1) ? ans : n - (j - i + 1));
    }
  }
  return ans;
}