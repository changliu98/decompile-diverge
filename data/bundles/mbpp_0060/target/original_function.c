int func0(int arr[], int n) {
  int *mls = (int *)malloc(n * sizeof(int));
  int max = 0;
  for (int i = 0; i < n; i++) {
    mls[i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (abs(arr[i] - arr[j]) <= 1 && mls[i] < mls[j] + 1) {
        mls[i] = mls[j] + 1;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (max < mls[i]) {
      max = mls[i];
    }
  }
  free(mls);
  return max;
}