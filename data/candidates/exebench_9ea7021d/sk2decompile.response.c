static void AdjustSpan(int *x, int *w, int max) {
  if (*x < 0) {
    *w += *x;
    *x = 0;
  }
  if (*x + *w > max) {
    *w = max - *x;
  }
}