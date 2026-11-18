bool func0(int *arr, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (arr[i] + arr[j] == 0) {
        return true;
      }
    }
  }
  return false;
}