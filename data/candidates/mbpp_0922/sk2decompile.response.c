void func0(int *arr, int n, int *max1, int *max2) {
  int i, j;
  if (n < 2) {
    *max1 = 0;
    *max2 = 0;
    return;
  }
  *max1 = arr[0];
  *max2 = arr[1];
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (arr[i] * arr[j] > *max1 * *max2) {
        *max1 = arr[i];
        *max2 = arr[j];
      }
    }
  }
}