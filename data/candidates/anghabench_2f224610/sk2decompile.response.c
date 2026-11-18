bool is_dup(int *arr, int len, int val) {
  int i;
  for (i = 0; i < len; i++) {
    if (arr[i] == val) {
      return true;
    }
  }
  return false;
}