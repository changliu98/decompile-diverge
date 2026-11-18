void findMinMax(long *arr, long *min, long *max) {
  int i;
  for (i = 1; i < 5; i++) {
    if (arr[i] < *min) *min = arr[i];
    if (arr[i] > *max) *max = arr[i];
  }
}