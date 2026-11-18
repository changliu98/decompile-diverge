int func0(float *x, int n) {
  int i, dec = 0, inc = 0;
  for (i = 1; i < n; i++) {
    if (x[i] > x[i - 1]) inc = 1;
    if (x[i - 1] > x[i]) dec = 1;
  }
  if (dec + inc == 2)
    return 0;
  else
    return 1;
}