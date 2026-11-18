void adjust_mode_num(int *mode_num) {
  if (*mode_num >= 10) {
    *mode_num = 9;
  } else if (*mode_num < 0) {
    *mode_num = 0;
  }
}