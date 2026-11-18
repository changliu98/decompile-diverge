void limit2_u16(unsigned short *x, unsigned short min, unsigned short max) {
  if (*x >= max) {
    *x = max;
  } else if (*x <= min) {
    *x = min;
  }
}