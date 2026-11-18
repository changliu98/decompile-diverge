bool _is_all_less_than(int *arr, int len, int val) {
  int i;
  for (i = 0; i < len; i++) {
    if (arr[i] >= val) {
      return false;
    }
  }
  return true;
}