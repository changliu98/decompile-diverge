bool __is_sorted(int* arr, int n) {
  if (n == 0) {
    return true;
  }
  for (int i = 1; i < n; i++) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
    if (i >= 2 && arr[i] == arr[i - 1] && arr[i] == arr[i - 2]) return false;
  }
  return true;
}