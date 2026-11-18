void upzero(int sign, int *s, int *y) {
  int i, j;
  if (sign == 0) {
    for (i = 0; i < 6; i++) y[i] = (y[i] * 255L) >> 8;
  } else {
    for (i = 0; i < 6; i++) {
      if (sign * s[i] >= 0)
        j = 128;
      else
        j = -128;
      y[i] = j + ((y[i] * 255L) >> 8);
    }
  }
  s[5] = s[4];
  s[4] = s[3];
  s[3] = s[2];
  s[1] = s[0];
  s[0] = sign;
}