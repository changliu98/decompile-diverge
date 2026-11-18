void next(int *i, int *j, int n) {
  *j = *j + 1;
  if (*j == n) {
    *j = 0;
    *i = *i + 1;
  }
}