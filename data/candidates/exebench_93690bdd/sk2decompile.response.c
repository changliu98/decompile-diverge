void limit2_i32(int *x, int min, int max) {
  if (*x >= max) {
    *x = max;
  } else if (*x <= min) {
    *x = min;
  }
}