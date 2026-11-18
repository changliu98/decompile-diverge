void clamp(int *x, int *y, int n) {
  *y += *x / n;
  *x %= n;
  if (*x < 0) {
    *y -= 1;
    *x += n;
  }
}