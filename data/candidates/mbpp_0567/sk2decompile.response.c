bool _is_sorted(int *arr, int len) {
  int i;
  for (i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
}