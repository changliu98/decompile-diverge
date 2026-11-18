void AdjustSpan2(int *x, int *w, int *s, int max) {
  if (*x < 0) {
    *s += *x;
    *w -= *x;
    *x = 0;
  }
  if (*x + *s > max) {
    *s = max - *x;
  }
}