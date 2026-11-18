void add_and_divide(int *x, int *y, int n) {
  *y += *x / n;
  *x %= n;
}