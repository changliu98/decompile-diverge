int C_Utils_compare_float_ptr(const void *a, const void *b) {
  float f1 = *(float *)a;
  float f2 = *(float *)b;

  if (f1 == f2) {
    return 0;
  } else if (f1 < f2) {
    return -1;
  } else {
    return 1;
  }
}