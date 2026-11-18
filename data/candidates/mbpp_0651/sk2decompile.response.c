bool _check_all_in(int *a, int a_len, int *b, int b_len) {
  int i, j;
  bool found;
  for (i = 0; i < b_len; i++) {
    found = false;
    for (j = 0; j < a_len; j++) {
      if (b[i] == a[j]) {
        found = true;
        break;
      }
    }
    if (!found) return false;
  }
  return true;
}