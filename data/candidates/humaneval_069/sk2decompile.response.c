int _find_majority(int *arr, int n) {
  int *counts = calloc(n + 1, sizeof(int));
  int majority = -1;
  for (int i = 0; i < n; i++) {
    counts[arr[i]]++;
    if (counts[arr[i]] >= arr[i] && arr[i] > majority) {
      majority = arr[i];
    }
  }
  free(counts);
  return majority;
}