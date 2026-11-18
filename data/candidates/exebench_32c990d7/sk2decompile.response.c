static void conv_sign(int sign, int *val) {
  if (*val & sign) {
    *val = (sign << 1) - *val;
    *val = -*val;
  }
}