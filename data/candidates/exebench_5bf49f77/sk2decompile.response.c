float catmull_rom_val(int n, float *x, float xi, float *y, float *dydx) {
  int i, j;
  float h, t, t2, t3, b0, b1, b2;
  j = n - 2;
  for (i = 0; i < n - 2; i++) {
    if (x[i + 1] > xi) {
      j = i;
      break;
    }
  }
  h = x[j + 1] - x[j];
  t = (xi - x[j]) / h;
  t2 = t * t;
  t3 = t2 * t;
  b0 = 1.0f + t3 - 3.0f * t2 + 3.0f * t;
  b1 = t2 - 2.0f * t2 + t;
  b2 = 3.0f * t2 - 3.0f * t3 + t;
  return b0 * y[j] + b1 * h * dydx[j] + b2 * y[j + 1] + t3 * h * dydx[j + 1];
}