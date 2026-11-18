int C_Utils_compare_float_ptr(const void *a, const void *b) {
  float *fa = (float *)a;
  float *fb = (float *)b;
  if (*fa == *fb) {
    return 0;
  } else if (*fa < *fb) {
    return -1;
  } else {
    return 1;
  }
}