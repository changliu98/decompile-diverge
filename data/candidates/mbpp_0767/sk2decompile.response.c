int func0(int *arr, int n, int k) {
  int i, j, count = 0;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (arr[i] + arr[j] == k) count++;
    }
  }
  return count;
}