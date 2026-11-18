void pick(int *x, int *y) {
  (*y)++;
  if (*y >= 768) {
    (*x)++;
    *y = 0;
  }
  if (*x >= 180) *x = 0;
}