int func0(int *arr, int n) {
  int max, i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (arr[i] < arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  max = arr[0];
  for (i = 1; i < n; i++) {
    max = max * 10 + arr[i];
  }
  return max;
}