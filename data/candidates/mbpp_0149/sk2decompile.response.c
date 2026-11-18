int func0(int *arr, int n) {
  int lis[n];
  for (int i = 0; i < n; i++) {
    lis[i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if ((arr[i] == arr[j] + 1 || arr[i] == arr[j] - 1) &&
          lis[i] < lis[j] + 1) {
        lis[i] = lis[j] + 1;
      }
    }
  }
  int max = 1;
  for (int i = 0; i < n; i++) {
    if (lis[i] > max) {
      max = lis[i];
    }
  }
  return max;
}