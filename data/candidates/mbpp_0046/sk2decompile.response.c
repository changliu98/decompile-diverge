bool _is_unique(int *arr, int len) {
  int i, j;
  for (i = 0; i < len; i++) {
    for (j = i + 1; j < len; j++) {
      if (arr[i] == arr[j]) {
        return false;
      }
    }
  }
  return true;
}