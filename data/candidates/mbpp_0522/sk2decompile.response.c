int func0(int *arr, int n) {
  int i, j, max;
  int lis[n + 1];
  int lds[n + 1];
  for (i = 0; i <= n; i++) {
    lis[i] = 1;
  }
  for (i = 1; i < n; i++) {
    for (j = 0; j < i; j++) {
      if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
        lis[i] = lis[j] + 1;
      }
    }
  }
  for (i = 0; i <= n; i++) {
    lds[i] = 1;
  }
  for (i = n - 2; i >= 0; i--) {
    for (j = n - 1; j > i; j--) {
      if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
        lds[i] = lds[j] + 1;
      }
    }
  }
  max = lds[0] + lis[0] - 1;
  for (i = 1; i < n; i++) {
    if (lds[i] + lis[i] - 1 > max) {
      max = lds[i] + lis[i] - 1;
    }
  }
  return max;
}