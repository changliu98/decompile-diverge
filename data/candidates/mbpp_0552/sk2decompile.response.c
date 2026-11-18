char *func0(int *arr, int n) {
  int diff[n - 1];
  for (int i = 1; i < n; i++) {
    diff[i - 1] = arr[i] - arr[i - 1];
  }
  for (int i = 1; i < n - 1; i++) {
    if (diff[i] != diff[0]) {
      char *str = "Non Linear Sequence";
      return str;
    }
  }
  char *str = "Linear Sequence";
  return str;
}