void parabolic_interpolation(float y2, float y1, float y0, int x1, float *x2,
                             int *x0) {
  float D;
  D = 0.5 * ((y2 - y0) / (y2 - 2.0 * y1 + y0));
  *x0 = x1 + (int)D;
  *x2 = y1 - 0.25 * (y2 - y0) * D;
}