int plot_digit_wierd(char c, float x, float y, float dx, float dy, float *xp,
                     float *yp) {
  int n = 0;
  int i, i0, i1;
  float dx1, dy1, x1, y1;
  if (c < '0' || c > '9') return 0;
  i0 = digit_index[c - '0'];
  i1 = digit_index[c - '0' + 1] - 1;
  for (i = i0; i <= i1; i++) {
    dx1 = dx * (digit_data[i] / 10);
    dy1 = dy * (digit_data[i] % 10);
    if (i != i0) {
      xp[n] = x1;
      yp[n] = y1;
      n++;
      xp[n] = x - dx1;
      yp[n] = y - dy1;
      n++;
    }
    x1 = x - dx1;
    y1 = y - dy1;
  }
  return n;
}