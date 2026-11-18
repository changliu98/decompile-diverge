bool _has_even(int *arr, int len) {
  int i;
  for (i = 0; i < len; i++) {
    if (arr[i] % 2 == 0) {
      return true;
    }
  }
  return false;
}