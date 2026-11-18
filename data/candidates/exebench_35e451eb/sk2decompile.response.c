void adjust_point(int *point) {
  if (*point < 0) {
    *point = 0;
  } else if (*point > 100) {
    *point = 100;
  }
}