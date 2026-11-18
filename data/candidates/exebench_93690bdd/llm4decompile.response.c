void limit2_i32(int32_t *x, int32_t lower, int32_t upper) {
  if (*x > upper) {
    *x = upper;
  } else if (*x < lower) {
    *x = lower;
  }
}