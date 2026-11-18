bool __array_equal(int *a, int *b, int len) {
  int i;
  for (i = 0; i < len; i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}