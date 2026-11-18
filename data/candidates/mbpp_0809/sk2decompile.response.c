bool _is_greater_than(int *a, int *b, int n) {
  int i;
  bool greater = true;
  for (i = 0; i < n; i++) {
    if (a[i] <= b[i]) {
      greater = false;
      break;
    }
  }
  return greater;
}